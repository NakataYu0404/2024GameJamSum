#include"Timer.h"

//シングルトン化
//---------------------------
//instanceの初期化
Timer* Timer::instance_ = nullptr;

Timer::Timer(void)
{
}

Timer::~Timer(void)
{
}

void Timer::Init(void)
{
	counter_ = COUNTER_ZERO;

	nowCount_ = GetNowCount();
}

void Timer::Update(void)
{
	if (GetNowCount() - nowCount_ >= SEC_2_MILLISEC)
	{
		nowCount_ = GetNowCount();
		counter_.Sec++;
	}
}

void Timer::Draw(void)
{

}

void Timer::Release(void)
{
}

void Timer::ResetTimer(void)
{
	nowCount_ = GetNowCount();
	counter_ = COUNTER_ZERO;
}

void Timer::CreateInstance(void)
{
	//instance_がnullptrの場合は初期化されたのち生成処理を行う
	if (instance_ == nullptr)
	{
		instance_ = new Timer();
	}

	instance_->Init();
}

Timer& Timer::GetInstance(void)
{
	return *instance_;
}

void Timer::Destroy(void)
{
	delete instance_;
	instance_ = nullptr;
}
