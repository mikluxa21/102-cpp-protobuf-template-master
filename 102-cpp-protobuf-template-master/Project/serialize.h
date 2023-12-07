#include <vector>
#include <memory>
#include <string>
#include <google/protobuf/message.h>
#include "parser/parser.h"

#if GOOGLE_PROTOBUF_VERSION <= 3012004
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong())
#else 
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize())
#endif

typedef std::vector<char> Data;
typedef std::shared_ptr<const Data> PointerToConstData;
typedef std::shared_ptr<Data> PointerToData;

template <class Message>
PointerToConstData serializeDelimited(const Message& msg)
{
	const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);//msg.byteSizeLong()
	const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);
	const PointerToData& result = std::make_shared<Data>(headerSize+messageSize);
	google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*> (&*result->begin());
	google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
	msg.SerializeWithCachedSizesToArray(buffer + headerSize);
	return result;
}


template <class MessageType>
std::list<std::shared_ptr<MessageType>> deserializeByDelimited(Data messages)
{
	typedef DelimitedMessagesStreamParser<MessageType> Parser;
	Parser parser;
	std::list<std::shared_ptr<MessageType>> result;
	for(const char byte: messages)
	{
		std::list<std::shared_ptr<MessageType>>& parsedMessages = parser.parse(std::string(1, byte));
		for(std::shared_ptr<MessageType>& value: parsedMessages)
		{
			result.push_back(value);
		}
	}
}
