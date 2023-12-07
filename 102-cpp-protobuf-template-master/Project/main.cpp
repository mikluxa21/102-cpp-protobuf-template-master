#include <iostream>
#include <gtest/gtest.h>
#include "file.pb.h"
#include "serialize.h"


typedef TestTask::Messages::WripperMessage WripperMessage;
typedef ::TestTask::Messages::FastResponse FastResponse;
typedef ::TestTask::Messages::SlowResponse SlowResponse;
typedef ::TestTask::Messages::RequestForFastResponse RequestForFastResponse;
typedef ::TestTask::Messages::RequestForSlowResponse RequestForSlowResponse;


WripperMessage createFastResponse(const std::string date_time)
{
	FastResponse *fastResponse = new FastResponse();
	fastResponse->set_current_date_time(date_time);
	WripperMessage wripperMessage;
	wripperMessage.set_allocated_fast_response(fastResponse);
	return wripperMessage;
}

WripperMessage createSlowResponse(int client_count)
{
	SlowResponse *slowResponse = new SlowResponse();
	slowResponse->set_connected_client_count(client_count);
	WripperMessage wripperMessage;
	wripperMessage.set_allocated_slow_response(slowResponse);
	return wripperMessage;
}

WripperMessage createRequestForFastResponse()
{
	RequestForFastResponse *requestForFastResponse = new RequestForFastResponse();
	WripperMessage wripperMessage;
	wripperMessage.set_allocated_request_for_fast_response(requestForFastResponse);
	return wripperMessage;
}

WripperMessage createRequestForSlowResponse(int seconds)
{
	RequestForSlowResponse *requestForSlowResponse = new RequestForSlowResponse();
	requestForSlowResponse->set_time_in_seconds_to_sleep(seconds);
	WripperMessage wripperMessage;
	wripperMessage.set_allocated_request_for_slow_response(requestForSlowResponse);
	return wripperMessage;
}

TEST(FastResponse, Deserialize)
{
	size_t *l;
	PointerToConstData pointerToConstData(serializeDelimited(createFastResponse("19581005T05017.333")));
	auto res = parseDelimited<WripperMessage>(static_cast<const void*> (&pointerToConstData), (size_t) 18, l);
	std::cout << ">>>" << (*res).fast_response().current_date_time() << std::endl;
	ASSERT_EQ((*res).fast_response().current_date_time(), "19581005T05017.333");
}

int main(int argc, char** argv)
{
	size_t *l;
	PointerToConstData pointerToConstData(serializeDelimited(createFastResponse("19581005T05017.333")));
				auto res = parseDelimited<WripperMessage>(static_cast<const void*> (&pointerToConstData), (size_t) 18, l);
				std::cout << ">>> " << (*res).fast_response().current_date_time() << std::endl;
	//::testing::InitGoogleTest(&argc, argv);
	return 0;//RUN_ALL_TESTS();
}

//testing::InitGoogleTest(&argc, argv);
//RUN_ALL_TESTS();
