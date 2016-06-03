#include	"game.h"
#pragma comment( linker, "/entry:mainCRTStartup" )
#pragma comment( linker, "/SUBSYSTEM:WINDOWS"    )
static void	myInitFunc( void );
static void	myDestoryFunc( void );
static void	myReshapeFunc( int width, int height );
static void	myIdleFunc( void );
static void	myDisplayFunc( void );
static void	myActivateFunc( int state );
static GSboolean gsSwapInterval( GSint Interval );
void main( int argc, char *argv[] )
{
	/* �n�������f�k�E�B���h�E�����������ĊJ�� */
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowPosition( WINDOW_POSX, WINDOW_POSY );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );

#if	FULL_SCREEN_MODE
	/* �t���X�N���[�����[�h */
	glutGameModeString( GAME_MODE_STRING );
	glutEnterGameMode();
	/* �t���X�N���[���̏ꍇ�̓}�E�X�J�[�\��������*/
	glutSetCursor(GLUT_CURSOR_NONE);
#else
	/* �E�B���h�E���[�h */
	glutCreateWindow( WINDOW_TITLE );
#endif

	/* �O���t�B�b�N�X�V�X�e���̏����� */
	gsInitGraphics();

	/* �T�E���h�V�X�e���̏����� */
	gsInitSound( (HWND)_glutGetHWND() );

	/* ���̓f�o�C�X�V�X�e���̏����� */
	gsInitInput( (HWND)_glutGetHWND() );

	/* �u����������L���ɂ��� */
	gsSwapInterval( 1 );

	/* �V�X�e���̏����� */
	myInitFunc();

	/* �I�������̊֐���ݒ肷�� */
	_glutDestroyFunc( myDestoryFunc );

	/* �E�B���h�E�T�C�Y�ύX���̊֐���ݒ� */
	glutReshapeFunc( myReshapeFunc );

	/* �\�������̊֐���ݒ� */
	glutDisplayFunc( myDisplayFunc );

	/* �C�x���g�̂Ȃ����̊֐���ݒ� */
	glutIdleFunc( myIdleFunc );

	/* �E�B���h�E���A�N�e�B�u�ɂȂ������̊֐���ݒ� */
	_glutActivateFunc( myActivateFunc );

	/* �t���[���^�C�}�̃��Z�b�g */
	gsFrameTimerReset();

	/* ���C�����[�v�������s�� */
	glutMainLoop();
}

/*-----------------------------------------------------------------------------
*
* Purpose : �����������D
*
* Return  : �Ȃ��D
*
*----------------------------------------------------------------------------*/
static void myInitFunc( void )
{
	/* �f�t�H���g�̃��C�g�p�����[�^ */
	static float	LightAmbient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
	static float	LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	static float	LightSpeclar[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	static float	LightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	/* �����̏����� */
	gsRandamize();

	/* ��ʃN���A���̃J���[�̐ݒ� */
	glClearColor( 0, 0,0, 1.0f );

	/* �ʃJ�����O�̏�����L���ɂ��� */
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	/* �f�v�X�o�b�t�@���P�D�O�ŃN���A����*/
	glClearDepth( 1.0 );

	/* �e�v�X�e�X�g��L���ɂ��� */
	glEnable( GL_DEPTH_TEST );

	/* �p�[�X�y�N�e�B�u�␳���s�� */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	/* �u�����h��L�� */
	glEnable( GL_BLEND );

	/* �f�t�H���g�̃u�����h����ݒ� */
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	/* �f�t�H���g�̎��_�ϊ��̕ϊ��s���ݒ肷�� */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(
		0.0f,  20.0f, 20.0f,
		0.0f,   0.0f,  0.0f,
		0.0f,   1.0f,  0.0f
	);

	/* �f�t�H���g�̃��C�g�̐ݒ� */
	glLightfv( GL_LIGHT0, GL_AMBIENT,  LightAmbient  );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,  LightDiffuse  );
	glLightfv( GL_LIGHT0, GL_SPECULAR, LightSpeclar  );
	glLightfv( GL_LIGHT0, GL_POSITION, LightPosition );
	glEnable( GL_LIGHT0 );

	/* ���C�e�B���O��L���ɂ��� */
	glEnable( GL_LIGHTING );

	/* �Q�[������������ */
	gameInit();
}

/*-----------------------------------------------------------------------------
*
* Purpose : �I�������D
*
* Return  : �Ȃ��D
*
*----------------------------------------------------------------------------*/
static void	myDestoryFunc( void )
{
	/* �Q�[���I������ */
	gameFinish();

	/* ���̓f�o�C�X�V�X�e���̏I������ */
	gsFinishInput();

	/* �T�E���h�V�X�e���̏I������ */
	gsFinishSound();
}

/*-----------------------------------------------------------------------------
*
* Purpose : �E�B���h�E�T�C�Y�ύX���̏����D
*
* Return  : �Ȃ��D
*
*----------------------------------------------------------------------------*/
static void myReshapeFunc( int width, int height )
{
	/* �������O�ɂȂ�Ȃ��悤�ɒ��� */
	height = ( height == 0 ) ? 1: height;

	/* �r���[�|�[�g�̐ݒ� */
	glViewport( 0, 0, width, height );

	/* �����ˉe�̕ϊ��s���ݒ肷�� */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(
		PERSPECTIVE_FOV,
		(float)width / (float)height,
		PERSPECTIVE_NEAR,
		PERSPECTIVE_FAR
	);

	/* ���f���r���[���[�h�ɂ��� */
	glMatrixMode( GL_MODELVIEW );
}

/*-----------------------------------------------------------------------------
*
* Purpose : �C�x���g�̂Ȃ����̏����D�i �Q�[�����C������ �j
*
* Return  : �Ȃ��D
*
*----------------------------------------------------------------------------*/
static void myIdleFunc( void )
{
	/* �t���[���^�C�}�̍X�V */
	gsFrameTimerUpdate();

	do
	{
		/* ���̓f�o�C�X�̓ǂݍ��� */
		gsReadInput();

		/* �Q�[�����C������ */
		gameMain();

		/* �G�X�P�[�v�L�[�������ꂽ���H */
		if ( GetAsyncKeyState( VK_ESCAPE ) != 0 ) {
#if	FULL_SCREEN_MODE
			/* �Q�[�����[�h���I������ */
			glutLeaveGameMode();
#else
			/* �I���������Ăяo�� */
			myDestoryFunc();
#endif
			/* �����I������ */
			exit( 0 );
		}
	} while ( gsFrameTimerIsSkip() == GS_TRUE );

	/* �`�揈�����Ăяo�� */
	glutPostRedisplay();
}

/*-----------------------------------------------------------------------------
*
* Purpose : �`�揈���D
*
* Return  : �Ȃ��D
*
*----------------------------------------------------------------------------*/
static void myDisplayFunc( void )
{
	/* ��ʃN���A */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	/* �Q�[���`�揈�� */
	gameDraw();

	/* �_�u���o�b�t�@�̐؂�ւ� */
	glutSwapBuffers();

	/* �^�C�}�E�F�C�g���s�� */
	gsFrameTimerWait();
}

/*-----------------------------------------------------------------------------
*
* Purpose : �E�B���h�E���A�N�e�B�u�ɂȂ������̏����D
*
* Return  : �Ȃ��D
*
*----------------------------------------------------------------------------*/
static void myActivateFunc( int state )
{
	/* ���̓f�o�C�X�V�X�e���ɃA�N�e�B�u��Ԃ�`���� */
	gsActivateInput( state );

	/* �T�E���h�V�X�e���ɃA�N�e�B�u��Ԃ�`���� */
	gsActivateSound( state );
}

/*-----------------------------------------------------------------------------
*
* Purpose : �X���b�v�C���^�[�o���̐ݒ�D�i �u���������̗L���E���� �j
*
* Return  : �Ȃ��D
*
*----------------------------------------------------------------------------*/
static GSboolean gsSwapInterval( GSint Interval )
{
	/* wglSwapIntervalEXT�g���֐��̃|�C���^�֐��^ */
	typedef BOOL (WINAPI * LPFNWGLSWAPINTERVALEXTPROC)( int interval );

	LPFNWGLSWAPINTERVALEXTPROC	wglSwapIntervalEXT = NULL;

	/* SwapIntervalEXT�̊֐��|�C���^���擾 */
	wglSwapIntervalEXT = (LPFNWGLSWAPINTERVALEXTPROC)
		wglGetProcAddress( "wglSwapIntervalEXT" );

	/* SwapIntervalEXT�֐����擾�ł������H */
	if ( wglSwapIntervalEXT != NULL )
	{
		/* �X���b�v�̃C���^�[�o����ݒ� */
		wglSwapIntervalEXT( Interval );

		return	GS_TRUE;
	}

	return	GS_FALSE;
}

/********** End of File ******************************************************/
