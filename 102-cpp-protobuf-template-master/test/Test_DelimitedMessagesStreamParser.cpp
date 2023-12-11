#include "../src/protobuf_parser/DelimitedMessagesStreamParser.hpp"
#include "../src/protobuf/message.pb.h"
#include <gtest/gtest.h>


typedef TestTask::Messages::WrapperMessage WrapperMessage;
typedef ::TestTask::Messages::FastResponse FastResponse;
typedef ::TestTask::Messages::SlowResponse SlowResponse;
typedef ::TestTask::Messages::RequestForFastResponse RequestForFastResponse;
typedef ::TestTask::Messages::RequestForSlowResponse RequestForSlowResponse;

WrapperMessage createFastResponse(const std::string date_time)
{
	FastResponse *fastResponse = new FastResponse();
	fastResponse->set_current_date_time(date_time);
	WrapperMessage wrapperMessage;
	wrapperMessage.set_allocated_fast_response(fastResponse);
	return wrapperMessage;
}

WrapperMessage createSlowResponse(int client_count)
{
	SlowResponse *slowResponse = new SlowResponse();
	slowResponse->set_connected_client_count(client_count);
	WrapperMessage wrapperMessage;
	wrapperMessage.set_allocated_slow_response(slowResponse);
	return wrapperMessage;
}

WrapperMessage createRequestForFastResponse()
{
	RequestForFastResponse *requestForFastResponse = new RequestForFastResponse();
	WrapperMessage wrapperMessage;
	wrapperMessage.set_allocated_request_for_fast_response(requestForFastResponse);
	return wrapperMessage;
}

WrapperMessage createRequestForSlowResponse(int seconds)
{
	RequestForSlowResponse *requestForSlowResponse = new RequestForSlowResponse();
	requestForSlowResponse->set_time_in_seconds_to_sleep(seconds);
	WrapperMessage wrapperMessage;
	wrapperMessage.set_allocated_request_for_slow_response(requestForSlowResponse);
	return wrapperMessage;
}

TEST(FastResponse, Deserialize)
{
	size_t *l;
	size_t len = 18;
	PointerToConstData pointerToConstData(serializeDelimited(createFastResponse("19581005T05017.333")));
	DelimitedMessagesStreamParser<WrapperMessage> parser;
	std::list<std::shared_ptr<const WrapperMessage>> res = parser.parse(std::string(pointerToConstData->begin(), pointerToConstData->end()));
	auto d = std::make_shared<WrapperMessage> (res.pop_back());
	ASSERT_TRUE(false);
}



