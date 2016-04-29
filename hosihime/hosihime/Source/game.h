
#ifndef		_GAME_H_
#define		_GAME_H_

#include	<GL/glut.h>
#include	<gslib.h>

/*---- ウィンドウパラメータ -------------------------------------------------*/

#define	WINDOW_TITLE		"Hoshinoriorihime"	/* ウィンドウタイトル	*/
#define	WINDOW_POSX			0				/* ウィンドウのｘ座標	*/
#define	WINDOW_POSY			0				/* ウィンドウのｙ座標	*/
#define	WINDOW_WIDTH		1280			/* ウィンドウの幅		*/
#define	WINDOW_HEIGHT		720				/* ウィンドウの高さ		*/
#define	FULL_SCREEN_MODE	0   			/* フルスクリーンモード	*/
#define	GAME_MODE_STRING	"1280x720:16@9"	/* 画面モード			*/

/*---- 視野変換パラメータ ---------------------------------------------------*/

#define	PERSPECTIVE_FOV		60.0f			/* 視野角				*/
#define	PERSPECTIVE_NEAR	0.1f			/* 近クリップ面			*/
#define	PERSPECTIVE_FAR		300.0f			/* 遠クリップ面			*/

/*---- ウェイトタイマ -------------------------------------------------------*/

#define	FPS_WAIT_TIME		( 1000 / 60 )	/* ＦＰＳウェイトタイマ */

/****** 関数プロトタイプ宣言 *************************************************/

extern void gameInit( void );				/* ゲーム初期化処理		*/
extern void gameMain( void );				/* ゲームメイン処理		*/
extern void gameDraw( void );				/* ゲーム描画処理		*/
extern void gameFinish( void );				/* ゲーム終了処理		*/

#endif

/********** End of File ******************************************************/
