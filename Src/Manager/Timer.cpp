#include"../Application.h"
#include"Timer.h"

//�V���O���g����
//---------------------------
//instance�̏�����
Timer* Timer::instance_ = nullptr;

Timer::Timer(void)
{
	timerFrameImg_ = 0;
	counter_ = COUNTER_ZERO;
	nowCount_ = 0;
	framePos_ = { 0,0 };
}

Timer::~Timer(void)
{
}

void Timer::Init(void)
{
	//�摜�ǂݍ���
	timerFrameImg_ = LoadGraph((Application::PATH_IMAGE + "TimerFrame.png").c_str());

	LoadDivGraph((Application::PATH_IMAGE + "Number.png").c_str(), 10, 10, 1, NUMBER_SIZE_X, NUMBER_SIZE_Y, numberImg_);

	//�ϐ��̏�����
	counter_ = COUNTER_ZERO;
	nowCount_ = GetNowCount();
	framePos_ = { Application::SCREEN_SIZE_X / 2, FRAME_SIZE_Y / 2 };
}

void Timer::Update(void)
{
	//���Ԍv��
	if (GetNowCount() - nowCount_ >= SEC_2_MILLISEC && TIME_LIMIT.Sec - counter_.Sec > 0)
	{
		nowCount_ = GetNowCount();
		counter_.Sec++;
	}
}

void Timer::Draw(void)
{
	//�g�̕`��
	DrawRotaGraph(framePos_.x, framePos_.y + 10, 1.0, 0.0, timerFrameImg_, true);

	//�����̕`��
	DrawRotaGraph(framePos_.x, framePos_.y + 10, 1.0, 0.0, numberImg_[(TIME_LIMIT.Sec - counter_.Sec) / 10], true);
	DrawRotaGraph(framePos_.x  + NUMBER_SIZE_X, framePos_.y + 10, 1.0, 0.0, numberImg_[(TIME_LIMIT.Sec - counter_.Sec) % 10], true);
}

void Timer::Release(void)
{
}

void Timer::ResetTimer(void)
{
	nowCount_ = GetNowCount();
	counter_ = COUNTER_ZERO;
}

bool Timer::IsTimeOver(void)
{
	return counter_.Sec >= TIME_LIMIT.Sec;
}

void Timer::CreateInstance(void)
{
	//instance_��nullptr�̏ꍇ�͏��������ꂽ�̂������������s��
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
