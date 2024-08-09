#include"../Application.h"
#include"../Manager/SceneManager.h"
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

	LoadDivGraph((Application::PATH_IMAGE + "Number.png").c_str()
		, NUMBER_ALL_DIV
		, NUMBER_X_DIV
		, NUMBER_Y_DIV
		, NUMBER_SIZE_X
		, NUMBER_SIZE_Y
		, numberImg_);

	//�ϐ��̏�����
	ResetTimer();
	framePos_ = { Application::SCREEN_SIZE_X / 2, FRAME_SIZE_Y / 2 + FRAME_SHIFT_POS_Y };
	ResetCountDownTimer();
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
	DrawRotaGraph(framePos_.x, framePos_.y, 1.0, 0.0, timerFrameImg_, true);

	//�����̕`��
	DrawRotaGraph(framePos_.x, framePos_.y, 1.0, 0.0, numberImg_[(TIME_LIMIT.Sec - counter_.Sec) / 10], true);
	DrawRotaGraph(framePos_.x  + NUMBER_SIZE_X, framePos_.y, 1.0, 0.0, numberImg_[(TIME_LIMIT.Sec - counter_.Sec) % 10], true);
}

void Timer::CountDownDraw(void)
{
	//�J�E���g�_�E���^�C�}�[���Z�b�g����Ă���Ȃ�
	if (countDownTime_ != 0.0f)
	{
		//�J�E���g�_�E���̕`��
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2
			, Application::SCREEN_SIZE_Y / 2
			, 3.0
			, 0.0
			, numberImg_[static_cast<int>(countDownTime_ - countDownCounter_) + 1]
			, true);
	}
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

bool Timer::CountDown(const float _countTime)
{
	countDownTime_ = _countTime;
	countDownCounter_ += SceneManager::GetInstance().GetDeltaTime();

	//�w��b���o������
	if (countDownCounter_ > _countTime)
	{
		//�J�E���^�̏�����
		ResetCountDownTimer();

		//�w��b���o����
		return true;
	}

	//�w��b���o���Ă��Ȃ�
	return false;
}

void Timer::ResetCountDownTimer(void)
{
	countDownCounter_ = 0.0f;
	countDownTime_ = 0.0f;
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
