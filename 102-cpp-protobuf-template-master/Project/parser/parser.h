#include <memory>
#include <vector>
#include <string>
#include <list>



template <class Message>
std::shared_ptr<Message> parseDelimited(const void* data, size_t size, size_t* bytesConsumed = 0)
{
	const std::vector<char> *buffer = static_cast<const std::vector<char>*> (data);
	Message *resMessage = new Message();
	for(size_t i = 0; i < size; i++)
	{
		if((*buffer)[i] <= size - i)
			if(resMessage->ParseFromString(std::string(buffer->begin() + i + 1, buffer->end())))
			{
				*bytesConsumed = size - i;
				return std::make_shared<Message> (*resMessage);
		}
	}
	return NULL;
}


template<class MessageType>
class DelimitedMessagesStreamParser
{
public:
typedef std::shared_ptr<const MessageType> PointerToConstValue;
	std::list<PointerToConstValue> parse(const std::string& data)
	{
		m_buffer.push_back(data[0]);
		size_t *byteConsumed;
		auto resParse = parseDelimited<MessageType>(static_cast<const void*> (&m_buffer), m_buffer.size(), byteConsumed);
		if(resParse != NULL)
		{
			std::list<PointerToConstValue> result = *resParse;
			m_buffer.clear();
			return result;
		}
		return NULL;
	}
private:
	std::vector<char> m_buffer = {};
};
