#include"Block.h"
#include"DxLib.h"
#include"InputControl.h"

/************************************
�}�N����`
*************************************/

#define FIELD_HEIGHT  (21)				//�t�B�[���h�̃}�X�̍���
#define FIELD_WIDTH  (12)               //�t�B�[���h�̃}�X�̕�
#define BLOCK_TROUT_SIZE  (4)  //�u���b�N�̃}�X�T�C�Y
#define BLOCK_SIZE  (36)  //1�u���b�N������̃T�C�Y
#define BLOCK_TYPE_MAX (7) //�����Ă���u���b�N�̎��
#define BLOCK_NEXT_POS_X  (700)  //���̃u���b�N�̍��W(X���W)
#define BLOCK_NEXT_POS_Y  (500)   //���̃u���b�N�̍��W�iy���W�j
#define BLOCK_STOCK_POS_X  (500)  //�X�g�b�N���ꂽ�u���b�N�̍��W�i�����W�j
#define BLOCK_STOCK_POS_Y  (350)  //�X�g�b�N���ꂽ�u���b�N�̍��W�i�x���W�j
#define DROP_BLOCK_INIT_X  (4)    //�����Ă���u���b�N�̏����i�w���W�j
#define DROP_BLOCK_INIT_Y  (-1)   //�����Ă��郔���b�N�̏����x���W
#define DROP_SPEED  (60)    //��������
#define TURN_CROCKWICE  (0)   //���v���ɉ�]������
#define TURN_ANTICROCKWICE  (1)  //�����v���ɉ�]������

/************************************
�^��`
*************************************/

enum BLOCK_STATE
{
	E_BLOCK_EMPTY,  //��u���b�N
	E_BLOCK_LIGHT_BLLUE,  //���F
	E_BLOCK_YELLOW_GREEN,  //����
	E_BLOCK_YELLOW,  //���F
	E_BLOCK_ORANGE,  //�I�����W
	E_BLOCK_BLUE,  //��
	E_BLOCK_PINK,  //�s���N
	E_BLOCK_RED,  //����
	E_BLOCK_GLAY,  //�D�F
	E_BLOCK_WALL,  //��
	E_BLOCK_IMAGE_MAX,  
};

/************************************
�萔��`
*************************************/
const int C_BLOCK_TABLE[BLOCK_TYPE_MAX][BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE] = {
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0},

	},
	{
		{0,0,0,0},
		{0,0,0,0},
		{2,2,2,2},
		{0,0,0,0},
},
	{
		{0,0,0,0},
		{3,0,0,0},
		{3,3,3,0},
		{0,0,0,0},
},
	{
		{0,0,0,0},
		{0,0,0,4},
		{0,4,4,4},
		{0,0,0,0},
},
	{
		{0,0,0,0},
		{0,5,5,0},
		{0,0,5,5},
		{0,0,0,0},
},
	{
		{0,0,0,0},
		{0,6,6,0},
		{6,6,0,0},
		{0,0,0,0},
},
	{
		{0,0,0,0},
		{0,7,0,0},
		{7,7,7,0},
		{0,0,0,0},
  },
};
/************************************
�ϐ��錾
*************************************/
int BlockImage[E_BLOCK_IMAGE_MAX];    //�u���b�N�摜
BLOCK_STATE Field[FIELD_HEIGHT][FIELD_WIDTH]; //�t�B�[���h�z��
BLOCK_STATE Next[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE]; //�ҋ@��Ԃ̃u���b�N
BLOCK_STATE Stock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE]; //�X�g�b�N�̃u���b�N
BLOCK_STATE DropBlock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];
int DropBlock_X;  //������u���b�N��X���W
int  DropBlock_Y;   //������u���b�N��Y���W

int waitTime;  //�ҋ@����
int Stock_Flg;  //�X�g�b�N�t���O
int Generate_Flg;  //�쐬�����t���O
int DeleteLine;    //���������C���̐�
int SoundEffect[3];  //SE

/************************************
�v���g�^�C�v�錾
*************************************/

void create_field(void);    //�t�B�[���h�̐�������
void create_block(void);    //�u���b�N�̐�������
void move_block(void);    //�u���b�N�̈ړ�����
void change_block(void);    //�X�g�b�N��������
void turn_block(int vlockwise);    //�u���b�N��]����
void check_overlap(int x,int y);    //�͈͊O�`�F�b�N����
void lock_block(int x, int y);    //���n�����u���b�N���Œ�ς݂ɕύX���鏈��
void check_line(void);    //�u���b�N�̉����m�F����

/************************************
*�u���b�N�@�\�G����������
* �����F�Ȃ�
* �߂�l�F�G���[���i-1�F�ȏ�A����ȊO:����j
*************************************/

int Block_Initialize(void)
{
	int ret = 0;  //�߂�l
	int  i = 0;

	//�u���b�N�摜�̓ǂݍ���
	ret = LoadDivGraph("images/block.png", E_BLOCK_IMAGE_MAX, 10, 1, BLOCK_SIZE, BLOCK_SIZE, BlockImage);

	//SE�̓ǂݍ���
	SoundEffect[0] = LoadSoundMem("sounds/SE3.mp3");
	SoundEffect[1] = LoadSoundMem("sounds/SE4.mp3");
	SoundEffect[2] = LoadSoundMem("sounds/SE5.wav");

	//���ʂ̒���
	ChangeVolumeSoundMem(150, SoundEffect[0]);
	ChangeVolumeSoundMem(150, SoundEffect[1]);
	ChangeVolumeSoundMem(130, SoundEffect[2]);

	//�t�B�[���h�̐���
	create_field();

	//�u���b�N����
	create_block();
	create_block();

	//�ҋ@���Ԃ̏�����
	waitTime = 0;

	//�X�g�b�N�t���O�̏�����
	Stock_Flg = FALSE;
	
	//�����t���O�̏�����
	Generate_Flg = TRUE;

	//���������C���̐��̏�����
	DeleteLine = 0;

	//�G���[�`�F�b�N
	for (i = 0; i < 3; i++)
	{
		if (SoundEffect[i] == -1)
		{
			ret = -1;
			break;
		}

	}
	return ret;
}
/************************************
*�u���b�N�@�\�G�X�V����
* �����F�Ȃ�
* �߂�l�F�Ȃ�
*************************************/
void Block_Update(void)
{
	//�u���b�N�̈ړ�����
	move_block();

	//�u���b�N�̃X�g�b�N
	if ((GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) == TRUE) || (GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) == TRUE))
	{
		//�����\�ł����
		if (Generate_Flg == TRUE)
		{
			change_block(); //�X�g�b�N��������
			//�u���b�N�̊J�X�𐳈ʒu�ɂ���
		}
	}
	//�u���b�N�̉�]�i�����v���j
	if ((GetButtonDown(XINPUT_BUTTON_A) == TRUE) || (GetButtonDown(XINPUT_BUTTON_Y) == TRUE))
	{
		turn_block(TURN_ANTICROCKWICE);
	}

	//�u���b�N�̉�]�i���v���j
	if ((GetButtonDown(XINPUT_BUTTON_B) == TRUE) || (GetButtonDown(XINPUT_BUTTON_X) == TRUE))
	{
		turn_block(TURN_CROCKWICE);
	}     
	//��������
	waitTime;   //�J�E���^�̍X�V
	if (waitTime > DROP_SPEED)
	{
		if (check_overlap(DropBlock_X, DropBlock_Y + 1) == TRUE)
		{
			DropBlock_Y++;
		}
	}
}
}
}