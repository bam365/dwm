/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#999999";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#cccccc";
static const char selbordercolor[]  = "#ffff00";
static const char selbgcolor[]      = "#000000";
static const char selfgcolor[]      = "#00ab00";
static unsigned int borderpx        = 2;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static Bool showbar                 = True;     /* False means no bar */
static Bool topbar                  = False;     /* False means bottom bar */
static unsigned int gappx           = 4;

/* tagging */
static const char *tags[] = { "web", "util", "wk1", "wk2", "wk3", "play", "sys" };

static Rule rules[] = {
	/* class      instance    title       tags mask     isfloating  monitor*/
	{ "Gimp",     NULL,       NULL,       0,            True,       -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       True,       -1 },
};

/* layout(s) */
static float mfact      = 0.55;
static Bool resizehints = False; /* False means respect size hints in tiled resizals */

static Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T*]",     sizedtile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[B]",      bstack },    
	{ "[M]",      monocle },
	{ "[T]",      tile },    /* first entry is default */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define XF86AudioRaiseVolume    0x1008ff13
#define XF86AudioLowerVolume    0x1008ff11
#define XF86AudioMute           0x1008ff12 
#define XF86AudioNext           0x1008ff17
#define XF86AudioPrev           0x1008ff16
#define XF86AudioPlay           0x1008ff14


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
#define XTERM "urxvt"
#define VOLMIXER "Front"
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dselcmd[] = { "dsel.sh", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { XTERM, NULL };
static const char *ranger[] = { XTERM,  "-e", "ranger", NULL };
static const char *htop[] = { XTERM,  "-e", "htop", NULL };
static const char *ncmpcpp[] = { XTERM,  "-e", "ncmpcpp", NULL };
static const char *luakit[] = { "luakit", NULL };
static const char *firefox[] = { "firefox", NULL };
static const char *editconfig[] = { "gvim", "/home/blake/src/dwm-5.9/config.h", NULL };
static const char *volumeup[] = {"amixer", "-c", "0", "set", VOLMIXER, "2%+", NULL };
static const char *volumedown[] = {"amixer", "-c", "0", "set", VOLMIXER, "2%-", NULL };
static const char *volumemute[] = {"amixer", "-c", "0", "set", VOLMIXER, "0%", NULL };
static const char *mpcnext[] = {"mpc", "next", NULL };
static const char *mpcprev[] = {"mpc", "prev", NULL };
static const char *mpctoggle[] = {"mpc", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_semicolon,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Left,   cycleview,      {.i = -1 } },
	{ MODKEY,                       XK_comma,  cycleview,      {.i = -1 } },
	{ MODKEY,                       XK_Right,  cycleview,      {.i = +1 } },
	{ MODKEY,                       XK_period, cycleview,      {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,  nudge,    {.i = -20 } },
	{ MODKEY,                       XK_bracketright, nudge,    {.i = +20 } },
	{ MODKEY|Mod1Mask,              XK_r,      spawn,          {.v = ranger } },
	{ MODKEY|Mod1Mask,              XK_l,      spawn,          {.v = luakit } },
	{ MODKEY|Mod1Mask,              XK_h,      spawn,          {.v = htop } },
	{ MODKEY|Mod1Mask,              XK_e,      spawn,          {.v = editconfig } },
	{ MODKEY|Mod1Mask,              XK_f,      spawn,          {.v = firefox } },
	{ MODKEY|Mod1Mask,              XK_m,      spawn,          {.v = ncmpcpp } },
	{ MODKEY,                       XK_o,      spawn,          {.v = dselcmd } },
	{ 0,                            XF86AudioRaiseVolume,      spawn,  {.v = volumeup } },
	{ 0,                            XF86AudioLowerVolume,      spawn,  {.v = volumedown } },
	{ 0,                            XF86AudioMute,             spawn,  {.v = volumemute } },
	{ 0,                            XF86AudioNext,             spawn,  {.v = mpcnext } },
	{ 0,                            XF86AudioPrev,             spawn,  {.v = mpcprev } },
	{ 0,                            XF86AudioPlay,             spawn,  {.v = mpctoggle } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be a tag number (starting at 0),
 * ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

