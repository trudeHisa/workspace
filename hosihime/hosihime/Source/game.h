
#ifndef		_GAME_H_
#define		_GAME_H_

#include	<GL/glut.h>
#include	<gslib.h>

/*---- �E�B���h�E�p�����[�^ -------------------------------------------------*/

#define	WINDOW_TITLE		"Hoshinoriorihime"	/* �E�B���h�E�^�C�g��	*/
#define	WINDOW_POSX			0				/* �E�B���h�E�̂����W	*/
#define	WINDOW_POSY			0				/* �E�B���h�E�̂����W	*/
#define	WINDOW_WIDTH		1280			/* �E�B���h�E�̕�		*/
#define	WINDOW_HEIGHT		720				/* �E�B���h�E�̍���		*/
#define	FULL_SCREEN_MODE	0   			/* �t���X�N���[�����[�h	*/
#define	GAME_MODE_STRING	"1280x720:16@9"	/* ��ʃ��[�h			*/

/*---- ����ϊ��p�����[�^ ---------------------------------------------------*/

#define	PERSPECTIVE_FOV		60.0f			/* ����p				*/
#define	PERSPECTIVE_NEAR	0.1f			/* �߃N���b�v��			*/
#define	PERSPECTIVE_FAR		300.0f			/* ���N���b�v��			*/

/*---- �E�F�C�g�^�C�} -------------------------------------------------------*/

#define	FPS_WAIT_TIME		( 1000 / 60 )	/* �e�o�r�E�F�C�g�^�C�} */

/****** �֐��v���g�^�C�v�錾 *************************************************/

extern void gameInit( void );				/* �Q�[������������		*/
extern void gameMain( void );				/* �Q�[�����C������		*/
extern void gameDraw( void );				/* �Q�[���`�揈��		*/
extern void gameFinish( void );				/* �Q�[���I������		*/

#endif

/********** End of File ******************************************************/
