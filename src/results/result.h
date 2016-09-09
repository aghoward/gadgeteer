#ifndef Result_H
#define Result_H

#include <functional>

using namespace std;

template <class TSuccessData, class TFailureData>
class Result {
    private:
        TSuccessData successData;
        TFailureData failureData;
        bool isSuccess;

    public:
        Result(TSuccessData data) {
            this->successData = data;
            this->isSuccess = true;
        }

        Result(TFailureData data) {
            this->failureData = data;
            this->isSuccess = false;
        }

        template <typename TResultData>
            TResultData Match(function<TResultData (TSuccessData)> whenSuccessful, function<TResultData (TFailureData)> whenFailure) {
                return (this->isSuccess) ? whenSuccessful(this->successData) : whenFailure(this->failureData);
            }
};

#endif
