#ifndef LCDSCREENSPY_H
#define LCDSCREENSPY_H
#include <string>
#include <queue>
#include "../../Interfaces/LCDScreen.hpp"
#include <vector>

enum LCDCall {
    DisplayStatic,
    DisplayScroll,
    MoveToSecondLine
};

std::string lcdCallToString(LCDCall call) {
    switch (call) {
        case DisplayScroll:    return "DisplayScroll";
        case DisplayStatic:    return "DisplayStatic";
        case MoveToSecondLine: return "MoveToSecondLine";
        default:               return "Unknown";
    }
}

class LCDScreenSpy : public LCDScreen
{
private:
    std::queue<LCDCall> calls;
    std::queue<std::string> messages;
public:
    LCDScreenSpy() {}
    ~LCDScreenSpy() override {}
    
    void displayStatic(std::string msg) override 
    {
        calls.push(LCDCall::DisplayStatic);
        messages.push(msg);
    }

    void clear() override {}
    
    void moveToSecondLine() override {
        calls.push(LCDCall::MoveToSecondLine);
    }
    
    void displayScroll(std::string msg) override {
        calls.push(LCDCall::DisplayScroll);
        messages.push(msg);
    }

    void shouldCallInOrder(std::vector<LCDCall> expectedCalls, std::vector<std::string> expectedMsgs) {
        int i = 1;
        if (calls.empty())
        {
            throw std::runtime_error("Validating calls but no calls every made");
        }
        for (LCDCall ec : expectedCalls)
        {
            LCDCall call = calls.front();
            if (call != ec)
            {
                throw std::runtime_error(
                        "Expected call number " + std::to_string(i) +
                        " to be " + lcdCallToString(ec) +
                        " but got " + lcdCallToString(call)
                        );
            }
            if (call == LCDCall::DisplayScroll || call == LCDCall::DisplayStatic)
            {
                std::string msg = messages.front();
                if (expectedMsgs.empty()){
                    throw std::runtime_error("Validating msg but no expectedMsgs passed");
                }
                std::string expectedMsg = expectedMsgs.front();
                if (expectedMsg != "%i" && expectedMsg != msg)
                {
                    throw std::runtime_error(
                            "Expected call to me made with message " +
                            expectedMsg + " but got " + msg
                            );
                }
                expectedMsgs.erase(expectedMsgs.begin());
                messages.pop();
            }
            calls.pop();
            i++;
        }
    }

    void ShouldHaveNoCalls()
    {
        if (!calls.empty())
        {
            throw std::runtime_error("Expected no calls but there is a call");
        }
        if (!messages.empty())
        {
            throw std::runtime_error("Expected no messages but there is a message");
        }
    }
};
#endif
