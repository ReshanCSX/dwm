/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 3; /* border pixel of windows */
static const unsigned int gappx = 30;   /* gap pixel between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 0;            /* 0 means bottom bar */ 
static char *fonts[] = {"Ubuntu Mono:size=14:antialias=true", "Symbols Nerd Font:pixelsize=14:antialias=true:autohint=true"};
static const char dmenufont[] = {"Ubuntu Mono, nato, monospace:size=14"};
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static char normbgcolor[] = "#2b2b2b";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#565656";
static char selfgcolor[] = "#2c2c2c";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#8c8c8c";
static char *colors[][3] = {
    /*                 fg            bg           border    */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};
static const unsigned int alphas[][3] = {
    /*                fg       bg        border   */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *    WM_CLASS(STRING) = instance, class
     *    WM_NAME(STRING) = title
     */
    /* class instance, title, tags, mask, iscentered, isfloating, monitor */
    {"code-oss", NULL, NULL, 1, 0, 0, 0},
    {"Eclipse", NULL, NULL, 1, 0, 0, 0},
    {"Darktable", NULL, NULL, 1, 0, 0, 0},
    {"kdenlive", NULL, NULL, 1, 0, 0, 0},
    {"resolve", NULL, NULL, 1, 0, 0, 0},
    {"Spotify", NULL, NULL, 1, 0, 0, 0},
    {"spotify", NULL, NULL, 1, 0, 0, 0},

    {"Steam", NULL, NULL, 1 << 1, 0, 0, 0},
    {"Lutris", NULL, NULL, 1 << 1, 0, 0, 0},
    {"discord", NULL, NULL, 1 << 1, 0, 0, 0},
    {"jetbrains-idea-ce", NULL, NULL, 1 << 1, 0, 0, 0},

    {"dolphin", NULL, NULL, 1 << 2, 0, 0, 0},
    {"Tor Browser", NULL, NULL, 1 << 2, 0, 1, 0},
    {"Thunar", NULL, NULL, 1 << 2, 0, 0, 0},
    {"Org.gnome.Nautilus", NULL, NULL, 1 << 2, 0, 0, 0},
    {"org.gnome.Nautilus", NULL, NULL, 1 << 2, 0, 0, 0},
    {"transmission", NULL, NULL, 1 << 2, 0, 0, 0},
    {"Transmission-gtk", NULL, NULL, 1 << 2, 0, 0, 0},

    {"firefox", NULL, NULL, 1 << 2, 0, 0, 0},
    {"Chromium", NULL, NULL, 1 << 2, 0, 0, 0},
    {"Brave-browser", NULL, NULL, 1 << 2, 0, 0, 0},

    {"obs", NULL, NULL, 1 << 4, 0, 0, 0},
    {"Tenacity", NULL, NULL, 1 << 4, 0, 0, 0},
    {"Audacity", NULL, NULL, 1 << 4, 0, 0, 0},
    {"SimpleScreenRecorder", NULL, NULL, 1 << 4, 0, 0, 0},

    {"Pavucontrol", NULL, NULL, 1 << 5, 0, 0, 0},
    {"pavucontrol-qt", NULL, NULL, 1 << 5, 0, 0, 0},
    {"easyeffects", NULL, NULL, 1 << 5, 0, 0, 0},

};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,       "-fn",
                                 dmenufont,   "-nb", normbgcolor,    "-nf",
                                 normfgcolor, "-sb", selbordercolor, "-sf",
                                 selfgcolor,  NULL};
static const char *roficmd[] = {"rofi", "-show", "drun"};
static const char *termcmd[] = {"gnome-terminal"};
static const char *ivolume[] = {"amixer", "-D", "pulse", "sset",
                                "Master"
                                "5%+"};
static const char *dvolume[] = {"amixer", "-D", "pulse", "sset",
                                "Master"
                                "5%-"};

static Key keys[] = {
    /* modifier                     key                           function
       argument */
    //------------------------------------------------------------------//
    //                              volume                              //
    //------------------------------------------------------------------//

    /* { MODKEY|ShiftMask,             XK_plus,                        spawn,
       {.v = ivolume } }, */
    /* { MODKEY|ShiftMask,             XK_minus,                       spawn,
       {.v = dvolume } }, */
    //------------------------------------------------------------------//
    //                            processes                             //
    //------------------------------------------------------------------//
    {MODKEY, XK_o, spawn, {.v = dmenucmd}},
    {MODKEY, XK_p, killclient, {0}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},

    /* {MODKEY, XK_b, togglebar, {0}}, */

    //------------------------------------------------------------------//
    //                              focus                               //
    //------------------------------------------------------------------//
    {MODKEY, XK_n, focusstack, {.i = +1}},
    {MODKEY, XK_e, focusstack, {.i = -1}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},

    /* {MODKEY, XK_a, incnmaster, {.i = +1}}, */
    /* {MODKEY, XK_z, incnmaster, {.i = -1}}, */

    //------------------------------------------------------------------//
    //                             monitor                              //
    //------------------------------------------------------------------//
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},

    //------------------------------------------------------------------//
    //                              resize                              //
    //------------------------------------------------------------------//
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_i, setmfact, {.f = +0.05}},
    {MODKEY, XK_Tab, view, {0}},

    //------------------------------------------------------------------//
    //                             layouts                              //
    //------------------------------------------------------------------//
    {MODKEY, XK_w, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_q, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, togglefloating, {0}},
    /* {MODKEY | ShiftMask, XK_space, togglefloating, {0}}, */

    {MODKEY, XK_F5, xrdb, {.v = NULL}},

    //------------------------------------------------------------------//
    //                              layers                              //
    //------------------------------------------------------------------//
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_o, quit, {0}},

    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
