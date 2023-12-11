#include <memory>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include "helpers.hpp"

#ifndef SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_
#define SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_

template<class MessageType>
class DelimitedMessagesStreamParser
{
public:
typedef std::shared_ptr<const MessageType> PointerToConstValue;
	std::list<PointerToConstValue> parse(const std::string& data)
	{
		for(auto i: data) m_buffer.push_back(i);
		size_t *byteConsumed;
		auto resParse = parseDelimited<MessageType>(static_cast<const void*> (&m_buffer), m_buffer.size(), byteConsumed);
		if(resParse != NULL)
		{
			std::list<PointerToConstValue> result;
			result.push_back(resParse);
			m_buffer.clear();
			return result;
		}
		return std::list<PointerToConstValue>();
	}
private:
	std::vector<char> m_buffer = {};
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */
