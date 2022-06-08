#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
    template<typename T>
    void UNUSED(T&& a) { (void)(a); }
}

namespace QUIZ2 {

    class CallBack
    {
    public:
        // 发出委托单
        virtual void OrderInsert(
            bool isBuy,        // true：买单，false：卖单
            double price,      // 委托单价格
            uint32_t volume,   // 委托量
            uint64_t orderId   // 订单号
        ) = 0;

        // 撤单请求
        virtual void OrderCancel(
            uint64_t orderId // 撤销单号
        ) = 0;

        virtual ~CallBack() = default;
    };


    class Solution
    {
    public:
        // 发出委托单
        virtual void OrderInsert(
            bool isBuy,      // true：买单，false：卖单
            double price,    // 委托单价格
            uint32_t volume, // 委托量
            uint64_t orderId // 订单号
        ) = 0;

        // 撤单请求
        virtual void OrderCancel(
            uint64_t orderId // 撤销单号
        ) = 0;

        // 成交回报
        virtual void OnTrade(
            uint64_t orderId, // 成交单号
            uint32_t volume   // 成交量
        ) = 0;

        virtual ~Solution() = default;
    };


    class MySolution : public Solution
    {
    public:
        MySolution(CallBack&);

        // 发出委托单
        void OrderInsert(
            bool isBuy,      // true：买单，false：卖单
            double price,    // 委托单价格
            uint32_t volume, // 委托量
            uint64_t orderId // 订单号
        ) override;

        // 撤单请求
        void OrderCancel(
            uint64_t orderId // 撤销单号
        ) override;

        // 成交回报
        void OnTrade(
            uint64_t orderId, // 成交单号
            uint32_t volume   // 成交量
        ) override;

    private:
        CallBack& mCallBack;
        // TODO: 添加适当的成员变量
    };

    MySolution::MySolution(CallBack& callBack) : mCallBack(callBack)
    {
        UNUSED(mCallBack); // 用于避免报错，实现前删除类似行
    }

    void MySolution::OrderInsert(bool isBuy, double price, uint32_t volume, uint64_t orderId)
    {
        // TODO: 实现该函数，并优化其性能
        UNUSED(isBuy);
        UNUSED(price);
        UNUSED(volume);
        UNUSED(orderId);
    }

    void MySolution::OrderCancel(uint64_t orderId)
    {
        // TODO: 实现该函数，并优化其性能
        UNUSED(orderId);
    }

    void MySolution::OnTrade(uint64_t orderId, uint32_t volume)
    {
        // TODO: 实现该函数
        UNUSED(orderId);
        UNUSED(volume);
    }


namespace Test {

    class MockCallBack : public CallBack
    {
    public:
        MOCK_METHOD(void, OrderInsert, (bool isBuy, double price, uint32_t volume, uint64_t orderId));
        MOCK_METHOD(void, OrderCancel, (uint64_t orderId));
    };


    // 测试用例示例
    TEST(ProtectTest, ExampleCase) {
        ::testing::StrictMock<MockCallBack> mockCallBack;
        std::unique_ptr<Solution> s { new MySolution(mockCallBack) };

        // 委托单1
        EXPECT_CALL(mockCallBack, OrderInsert(true, 100, 20, 1));
        s->OrderInsert(true, 100, 20, 1);

        // 委托单2
        EXPECT_CALL(mockCallBack, OrderInsert(false, 101, 30, 2));
        s->OrderInsert(false, 101, 30, 2);

        // 委托单3
        EXPECT_CALL(mockCallBack, OrderInsert(true, 99, 10, 3));
        s->OrderInsert(true, 99, 10, 3);

        // 撤单请求1
        EXPECT_CALL(mockCallBack, OrderCancel(1));
        s->OrderCancel(1);

        // 成交回报
        s->OnTrade(3, 5);

        // 委托单4
        EXPECT_CALL(mockCallBack, OrderInsert(true, 99, 20, 4));
        s->OrderInsert(true, 99, 20, 4);

        // 委托单5
        {
            // 测试顺序调用
            ::testing::InSequence s;
            EXPECT_CALL(mockCallBack, OrderCancel(3));
            EXPECT_CALL(mockCallBack, OrderCancel(4));
            EXPECT_CALL(mockCallBack, OrderInsert(false, 98, 40, 5));
        }
        s->OrderInsert(false, 98, 40, 5);
    }


    // TODO: 添加更多测试用例
} /*Test*/ } /* QUIZ2 */