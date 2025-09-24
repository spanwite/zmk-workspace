#define ___ &trans
#define XXX &none

#define X_MEH      &sk LC(LS(LALT))
#define X_SEMI_MEH &sk LC(LSHFT)
#define X_HYPER    &sk LC(LS(LGUI))
#define X_ULTRA_HYPER &sk LC(LS(LA(LGUI)))

#ifndef X_CHNG_LNG
	#define X_CHNG_LNG &kp LS(LALT)
#endif

#define X_OVERLAY      Y_MEH(F1)
#define X_RECORD       Y_MEH(F2)
#define X_SCRNSHT      Y_MEH(F3)
#define X_REPLAY       Y_MEH(F4)
#define X_GIF          Y_MEH(F5)

// Shortcuts for Pomotroid (Pomodoro app for Windows)
#define X_TIMER_TOGGLE Y_MEH(Q)
#define X_TIMER_RESET  Y_MEH(W)
#define X_TIMER_SKIP   Y_MEH(E)

#ifdef OS_WINDOWS
	#define X_LOCK     &kp LG(L)
	#define X_SNIP     &kp LG(LS(S))
#else
	#define X_SLEEP    &kp K_SLEEP
	#define X_SHUTDOWN &kp K_PWR
	#define X_RESTART  &trans
	#define X_LOCK     &kp K_LOCK
	#define X_SNIP     &kp PRINTSCREEN
#endif

/*
* Symbols: Windows Alt Codes
* OS: Windows
* Features:
*	v Works as a text character when typing text
*	x Does not work as a shortcut in the apps
*	x Sometimes does not work in zmk macros
* Use it if you:
*	- have more than one keyboard layout
*	- want consistency in symbols typing
*	- don't want to install an external keyboard layout or modify the existing one
*	- are a Windows user
* */
#if defined(SYMBOLS_WINDOWS_ALT_CODES)
	#define X_COMMA   &mc_comma
	#define X_COLON   &mc_colon
	#define X_AT      &mc_at
	#define X_PIPE    &mc_pipe
	#define X_AMPS    &mc_amps
	#define X_LESS    &mc_less
	#define X_GRT     &mc_greater
	#define X_QST     &mc_qst
	#define X_LBKT    &mc_lbkt
	#define X_RBKT    &mc_rbkt
	#define X_SEMI    &mc_semi
	#define X_RBRC    &mc_rbrc
	#define X_LBRC    &mc_lbrc
	#define X_TILDE   &mc_tilde
	#define X_DQT     &mc_dqt
	#define X_DOT     &mc_dot
	#define X_DLLR    &mc_dllr
	#define X_CARET   &mc_caret
	#define X_SQT     &mc_sqt
/*
* Symbols: Custom Keyboard Layout
* OS: Any
* Features:
*	v Works as a text character when typing text
*	v Works as a shortcut in the apps
*	v Works in zmk macros
* Use it if you:
*	- have more than one keyboard layout
*	- want consistency in symbols typing
*	- can install external keyboard layout or modify an existing one
* */
#elif defined(SYMBOLS_CUSTOM_KEYBOARD_LAYOUT)
	#define X_COMMA &kp RA(N0)
	#define X_COLON &kp RA(N1)
	#define X_AT    &kp RA(N2)
	#define X_PIPE  &kp RA(N3)
	#define X_AMPS  &kp RA(N4)
	#define X_LESS  &kp RA(N5)
	#define X_GRT   &kp RA(N6)
	#define X_QST   &kp RA(N7)
	#define X_LBKT  &kp RA(N8)
	#define X_RBKT  &kp RA(N9)
	#define X_SEMI  &kp RS(RA(N0))
	#define X_RBRC  &kp RS(RA(N1))
	#define X_LBRC  &kp RS(RA(N2))
	#define X_TILDE &kp RS(RA(N3))
	#define X_DQT   &kp RS(RA(N4))
	#define X_DOT   &kp RS(RA(N5))
	#define X_DLLR  &kp RS(RA(N6))
	#define X_CARET &kp RS(RA(N7))
/*
* Symbols: Usual
* Features: Usual symbols that work nicely in English keyboard layout
* Use it if you:
*	- have only one English keyboard layout
* */
#else
	#define SYMBOLS_CLASSICAL
	#define X_COMMA &kp COMMA
	#define X_COLON &kp COLON
	#define X_AT    &kp AT
	#define X_PIPE  &kp PIPE
	#define X_AMPS  &kp AMPS
	#define X_LESS  &kp LT
	#define X_GRT   &kp GT
	#define X_QST   &kp QMARK
	#define X_LBKT  &kp LBKT
	#define X_RBKT  &kp RBKT
	#define X_SEMI  &kp SEMI
	#define X_RBRC  &kp RBRC
	#define X_LBRC  &kp LBRC
	#define X_TILDE &kp TILDE
	#define X_DQT   &kp DQT
	#define X_DOT   &kp DOT
	#define X_DLLR  &kp DLLR
	#define X_CARET &kp CARET
#endif
