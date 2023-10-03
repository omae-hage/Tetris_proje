/************************************
�v���O���~���O���K�i�e�g���X�Ӂj
*************************************/

#include"DxLib.h"
#include"FreamControl.h"
#include"SceneManager"
#include"InputControl.h"


/************************************
�}�N����`
*************************************/

#define SCREEN_HEIGHT(720)
#define SCREEN_WIDTH(1280)
#define SCREEN_COLORBIT(32)
#define SCREEN_SIZE(20)

/************************************
�^��`
*************************************/


/************************************
�O���[�o���ϐ��錾
*************************************/

/************************************
�v���g�^�C�v�錾
*************************************/

/************************************
�v���O�����̊J�n
*************************************/

int WINAPI WinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE hprevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)

{
	//�^�C�g����ύX
	SetMainWindowText("�e�g���X");

	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y�̌���
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);

	//Dx���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�t���[�������@�\����������
	FreamControl_Initialize();

	//�V�[���Ǘ��@�\����������
	SceneManager_Initialize(E_TITLE);

	//���͐����@�\����������
	InputControl_Initialize();

	//�`����ʂ𗠂ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//�����T�C�Y��ݒ�
	SetFontSize(FONT_SIZE);

	//�Q�[�����[�v
	while (processMessage() == 0 && GetExitButton() != TRUE && ErrorCheck() == D_NORMALITY)
	{
		//�t���[�����[�g�����@�\�X�V����
		FreamControl_Update();

		//��ʂ̏�����
		ClearDrawScreen();

		//���͐����X�V����
		InputControl_Update();

		//�V�[���Ǘ��@�\�X�V����
		SceneManager_Update();

		//�V�[���Ǘ��@�\�`�揈��
		SceneManager_Draw();

		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
		//DX���C�u�����g�p�̏I������
		DxLib_End();

		//���ӂƂ̏I��
		return 0;


}

