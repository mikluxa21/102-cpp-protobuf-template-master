#include <list>
#include <algorithm>
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
          std::list<PointerToConstValue> result;
          this->m_buffer.insert(this->m_buffer.end(), data.begin(), data.end());
          size_t bytesConsumed = 0;
          while(!this->m_buffer.empty())
          {
            auto msg = parseDelimited<MessageType>(this->m_buffer.data(), 
        				           this->m_buffer.size(),
        				           &bytesConsumed
     					          );
            if(bytesConsumed > 0)
            {
              result.push_back(msg);
              this->m_buffer.erase(this->m_buffer.begin(),
        		           this->m_buffer.begin() + bytesConsumed);
            }
            else
              break;
      }
    return result;
  }
private:
  std::vector<char> m_buffer = {};
};

#endif /* SRC_PROTOBUF_PARSER_DELIMITEDMESSAGESSTREAMPARSER_HPP_ */
