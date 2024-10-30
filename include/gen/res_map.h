#pragma once
#include <app/base.h>
#include <app/sdl2.h>

static int get_png_id(const char* file_name) {
   if (0) return -1;
   else if (STRNEQ(file_name, "bigFont.png", 37)) return 0;
   else if (STRNEQ(file_name, "colourPicker.png", 37)) return 1;
   else if (STRNEQ(file_name, "colourPickerBackground.png", 37)) return 2;
   else if (STRNEQ(file_name, "colourPickerOverlay.png", 37)) return 3;
   else if (STRNEQ(file_name, "colourPickerShadow.png", 37)) return 4;
   else if (STRNEQ(file_name, "huePickerBackground.png", 37)) return 5;
   else if (STRNEQ(file_name, "menuCircleWhite.png", 37)) return 6;
   else if (STRNEQ(file_name, "menuColourPanelBackground.png", 37)) return 7;
   else if (STRNEQ(file_name, "CCControlColourPickerSpriteSheet.png", 37)) return 8;
   else if (STRNEQ(file_name, "chatFont.png", 37)) return 9;
   else if (STRNEQ(file_name, "edit_barBG_001.png", 37)) return 10;
   else if (STRNEQ(file_name, "floor.png", 37)) return 11;
   else if (STRNEQ(file_name, "fps_images.png", 37)) return 12;
   else if (STRNEQ(file_name, "game_bg_01_001.png", 37)) return 13;
   else if (STRNEQ(file_name, "GJ_button_01.png", 37)) return 14;
   else if (STRNEQ(file_name, "GJ_button_02.png", 37)) return 15;
   else if (STRNEQ(file_name, "GJ_button_03.png", 37)) return 16;
   else if (STRNEQ(file_name, "GJ_button_04.png", 37)) return 17;
   else if (STRNEQ(file_name, "GJ_BPMOffBtn_001.png", 37)) return 18;
   else if (STRNEQ(file_name, "GJ_BPMOnBtn_001.png", 37)) return 19;
   else if (STRNEQ(file_name, "GJ_achBtn_001.png", 37)) return 20;
   else if (STRNEQ(file_name, "GJ_arrow_01_001.png", 37)) return 21;
   else if (STRNEQ(file_name, "GJ_arrow_02_001.png", 37)) return 22;
   else if (STRNEQ(file_name, "GJ_arrow_03_001.png", 37)) return 23;
   else if (STRNEQ(file_name, "GJ_audioOffBtn_001.png", 37)) return 24;
   else if (STRNEQ(file_name, "GJ_audioOnBtn_001.png", 37)) return 25;
   else if (STRNEQ(file_name, "GJ_autoOffBtn_001.png", 37)) return 26;
   else if (STRNEQ(file_name, "GJ_autoOnBtn_001.png", 37)) return 27;
   else if (STRNEQ(file_name, "GJ_checkpointBtn_001.png", 37)) return 28;
   else if (STRNEQ(file_name, "GJ_chrSel_001.png", 37)) return 29;
   else if (STRNEQ(file_name, "GJ_closeBtn_001.png", 37)) return 30;
   else if (STRNEQ(file_name, "GJ_completesIcon_001.png", 37)) return 31;
   else if (STRNEQ(file_name, "GJ_createBtn_001.png", 37)) return 32;
   else if (STRNEQ(file_name, "GJ_creatorBtn_001.png", 37)) return 33;
   else if (STRNEQ(file_name, "GJ_deleteBtn_001.png", 37)) return 34;
   else if (STRNEQ(file_name, "GJ_downloadsIcon_001.png", 37)) return 35;
   else if (STRNEQ(file_name, "GJ_editBtn_001.png", 37)) return 36;
   else if (STRNEQ(file_name, "GJ_featuredBtn_001.png", 37)) return 37;
   else if (STRNEQ(file_name, "GJ_fxOffBtn_001.png", 37)) return 38;
   else if (STRNEQ(file_name, "GJ_fxOnBtn_001.png", 37)) return 39;
   else if (STRNEQ(file_name, "GJ_garageBtn_001.png", 37)) return 40;
   else if (STRNEQ(file_name, "GJ_gkBtn_001.png", 37)) return 41;
   else if (STRNEQ(file_name, "GJ_gkOffBtn_001.png", 37)) return 42;
   else if (STRNEQ(file_name, "GJ_gkOnBtn_001.png", 37)) return 43;
   else if (STRNEQ(file_name, "GJ_helpBtn_001.png", 37)) return 44;
   else if (STRNEQ(file_name, "GJ_infoBtn_001.png", 37)) return 45;
   else if (STRNEQ(file_name, "GJ_infoIcon_001.png", 37)) return 46;
   else if (STRNEQ(file_name, "GJ_levelComplete_001.png", 37)) return 47;
   else if (STRNEQ(file_name, "GJ_likeBtn2_001.png", 37)) return 48;
   else if (STRNEQ(file_name, "GJ_likeBtn_001.png", 37)) return 49;
   else if (STRNEQ(file_name, "GJ_likesIcon_001.png", 37)) return 50;
   else if (STRNEQ(file_name, "GJ_lockGray_001.png", 37)) return 51;
   else if (STRNEQ(file_name, "GJ_lock_001.png", 37)) return 52;
   else if (STRNEQ(file_name, "GJ_longBtn01_001.png", 37)) return 53;
   else if (STRNEQ(file_name, "GJ_longBtn02_001.png", 37)) return 54;
   else if (STRNEQ(file_name, "GJ_longBtn03_001.png", 37)) return 55;
   else if (STRNEQ(file_name, "GJ_lvlEdit_001.png", 37)) return 56;
   else if (STRNEQ(file_name, "GJ_menuBtn_001.png", 37)) return 57;
   else if (STRNEQ(file_name, "GJ_moreGamesBtn_001.png", 37)) return 58;
   else if (STRNEQ(file_name, "GJ_musicOffBtn_001.png", 37)) return 59;
   else if (STRNEQ(file_name, "GJ_musicOnBtn_001.png", 37)) return 60;
   else if (STRNEQ(file_name, "GJ_nameTxt_001.png", 37)) return 61;
   else if (STRNEQ(file_name, "GJ_newBtn_001.png", 37)) return 62;
   else if (STRNEQ(file_name, "GJ_normalBtn_001.png", 37)) return 63;
   else if (STRNEQ(file_name, "GJ_noteIcon_001.png", 37)) return 64;
   else if (STRNEQ(file_name, "GJ_optionsBtn02_001.png", 37)) return 65;
   else if (STRNEQ(file_name, "GJ_optionsBtn_001.png", 37)) return 66;
   else if (STRNEQ(file_name, "GJ_pauseBtn_001.png", 37)) return 67;
   else if (STRNEQ(file_name, "GJ_pauseBtn_clean_001.png", 37)) return 68;
   else if (STRNEQ(file_name, "GJ_playBtn2_001.png", 37)) return 69;
   else if (STRNEQ(file_name, "GJ_playBtn_001.png", 37)) return 70;
   else if (STRNEQ(file_name, "GJ_practiceBtn_001.png", 37)) return 71;
   else if (STRNEQ(file_name, "GJ_practiceComplete_001.png", 37)) return 72;
   else if (STRNEQ(file_name, "GJ_rateDiffBtn2_001.png", 37)) return 73;
   else if (STRNEQ(file_name, "GJ_rateDiffBtn_001.png", 37)) return 74;
   else if (STRNEQ(file_name, "GJ_redoBtn_001.png", 37)) return 75;
   else if (STRNEQ(file_name, "GJ_removeCheckBtn_001.png", 37)) return 76;
   else if (STRNEQ(file_name, "GJ_replayBtn_001.png", 37)) return 77;
   else if (STRNEQ(file_name, "GJ_sDownloadIcon_001.png", 37)) return 78;
   else if (STRNEQ(file_name, "GJ_sLikeIcon_001.png", 37)) return 79;
   else if (STRNEQ(file_name, "GJ_sRecentIcon_001.png", 37)) return 80;
   else if (STRNEQ(file_name, "GJ_sTrendingIcon_001.png", 37)) return 81;
   else if (STRNEQ(file_name, "GJ_savedBtn_001.png", 37)) return 82;
   else if (STRNEQ(file_name, "GJ_searchBtn_001.png", 37)) return 83;
   else if (STRNEQ(file_name, "GJ_select_001.png", 37)) return 84;
   else if (STRNEQ(file_name, "GJ_shareBtn_001.png", 37)) return 85;
   else if (STRNEQ(file_name, "GJ_sideArt_001.png", 37)) return 86;
   else if (STRNEQ(file_name, "GJ_statsBtn_001.png", 37)) return 87;
   else if (STRNEQ(file_name, "GJ_table_bottom_001.png", 37)) return 88;
   else if (STRNEQ(file_name, "GJ_table_side_001.png", 37)) return 89;
   else if (STRNEQ(file_name, "GJ_table_top_001.png", 37)) return 90;
   else if (STRNEQ(file_name, "GJ_timeIcon_001.png", 37)) return 91;
   else if (STRNEQ(file_name, "GJ_topBar_001.png", 37)) return 92;
   else if (STRNEQ(file_name, "GJ_undoBtn_001.png", 37)) return 93;
   else if (STRNEQ(file_name, "GJ_unlockTxt_001.png", 37)) return 94;
   else if (STRNEQ(file_name, "GJ_updateBtn_001.png", 37)) return 95;
   else if (STRNEQ(file_name, "bump_01_001.png", 37)) return 96;
   else if (STRNEQ(file_name, "bump_01_glow_001.png", 37)) return 97;
   else if (STRNEQ(file_name, "chain_01_001.png", 37)) return 98;
   else if (STRNEQ(file_name, "checkpoint_01_001.png", 37)) return 99;
   else if (STRNEQ(file_name, "checkpoint_01_glow_001.png", 37)) return 100;
   else if (STRNEQ(file_name, "cocos2DxLogo.png", 37)) return 101;
   else if (STRNEQ(file_name, "d_spikes_01_001.png", 37)) return 102;
   else if (STRNEQ(file_name, "d_spikes_02_001.png", 37)) return 103;
   else if (STRNEQ(file_name, "d_spikes_03_001.png", 37)) return 104;
   else if (STRNEQ(file_name, "d_spikes_04_001.png", 37)) return 105;
   else if (STRNEQ(file_name, "developedBy_001.png", 37)) return 106;
   else if (STRNEQ(file_name, "diffIcon_01_btn_001.png", 37)) return 107;
   else if (STRNEQ(file_name, "diffIcon_02_btn_001.png", 37)) return 108;
   else if (STRNEQ(file_name, "diffIcon_03_btn_001.png", 37)) return 109;
   else if (STRNEQ(file_name, "diffIcon_04_btn_001.png", 37)) return 110;
   else if (STRNEQ(file_name, "diffIcon_05_btn_001.png", 37)) return 111;
   else if (STRNEQ(file_name, "difficultySelected_001.png", 37)) return 112;
   else if (STRNEQ(file_name, "difficulty_00_btn_001.png", 37)) return 113;
   else if (STRNEQ(file_name, "difficulty_01_btn_001.png", 37)) return 114;
   else if (STRNEQ(file_name, "difficulty_02_btn_001.png", 37)) return 115;
   else if (STRNEQ(file_name, "difficulty_03_btn_001.png", 37)) return 116;
   else if (STRNEQ(file_name, "difficulty_04_btn_001.png", 37)) return 117;
   else if (STRNEQ(file_name, "difficulty_05_btn_001.png", 37)) return 118;
   else if (STRNEQ(file_name, "edit_buildBtn_001.png", 37)) return 119;
   else if (STRNEQ(file_name, "edit_buildSBtn_001.png", 37)) return 120;
   else if (STRNEQ(file_name, "edit_ccwBtn_001.png", 37)) return 121;
   else if (STRNEQ(file_name, "edit_cwBtn_001.png", 37)) return 122;
   else if (STRNEQ(file_name, "edit_deleteBtn_001.png", 37)) return 123;
   else if (STRNEQ(file_name, "edit_deleteSBtn_001.png", 37)) return 124;
   else if (STRNEQ(file_name, "edit_deselectBtn_001.png", 37)) return 125;
   else if (STRNEQ(file_name, "edit_downBtn2_001.png", 37)) return 126;
   else if (STRNEQ(file_name, "edit_downBtn_001.png", 37)) return 127;
   else if (STRNEQ(file_name, "edit_eBGEOff_001.png", 37)) return 128;
   else if (STRNEQ(file_name, "edit_eBGEOn_001.png", 37)) return 129;
   else if (STRNEQ(file_name, "edit_eGhostDBtn_001.png", 37)) return 130;
   else if (STRNEQ(file_name, "edit_eGhostEBtn_001.png", 37)) return 131;
   else if (STRNEQ(file_name, "edit_eLevelEndBtn_001.png", 37)) return 132;
   else if (STRNEQ(file_name, "edit_eSettingsBtn_001.png", 37)) return 133;
   else if (STRNEQ(file_name, "edit_eStartPosBtn_001.png", 37)) return 134;
   else if (STRNEQ(file_name, "edit_eTintBGBtn_001.png", 37)) return 135;
   else if (STRNEQ(file_name, "edit_eTintGBtn_001.png", 37)) return 136;
   else if (STRNEQ(file_name, "edit_editBtn_001.png", 37)) return 137;
   else if (STRNEQ(file_name, "edit_editObjBtn_001.png", 37)) return 138;
   else if (STRNEQ(file_name, "edit_editSBtn_001.png", 37)) return 139;
   else if (STRNEQ(file_name, "edit_eeFBBtn_001.png", 37)) return 140;
   else if (STRNEQ(file_name, "edit_eeFLBtn_001.png", 37)) return 141;
   else if (STRNEQ(file_name, "edit_eeFRBtn_001.png", 37)) return 142;
   else if (STRNEQ(file_name, "edit_eeFTBtn_001.png", 37)) return 143;
   else if (STRNEQ(file_name, "edit_eeNoneBtn_001.png", 37)) return 144;
   else if (STRNEQ(file_name, "edit_eeSDBtn_001.png", 37)) return 145;
   else if (STRNEQ(file_name, "edit_eeSUBtn_001.png", 37)) return 146;
   else if (STRNEQ(file_name, "edit_flipXBtn_001.png", 37)) return 147;
   else if (STRNEQ(file_name, "edit_flipYBtn_001.png", 37)) return 148;
   else if (STRNEQ(file_name, "edit_leftBtn2_001.png", 37)) return 149;
   else if (STRNEQ(file_name, "edit_leftBtn_001.png", 37)) return 150;
   else if (STRNEQ(file_name, "edit_rightBtn2_001.png", 37)) return 151;
   else if (STRNEQ(file_name, "edit_rightBtn_001.png", 37)) return 152;
   else if (STRNEQ(file_name, "edit_swipeBtn_001.png", 37)) return 153;
   else if (STRNEQ(file_name, "edit_upBtn2_001.png", 37)) return 154;
   else if (STRNEQ(file_name, "edit_upBtn_001.png", 37)) return 155;
   else if (STRNEQ(file_name, "edit_vLine_001.png", 37)) return 156;
   else if (STRNEQ(file_name, "edit_zoomInBtn_001.png", 37)) return 157;
   else if (STRNEQ(file_name, "edit_zoomOutBtn_001.png", 37)) return 158;
   else if (STRNEQ(file_name, "exMark_001.png", 37)) return 159;
   else if (STRNEQ(file_name, "floorLine_001.png", 37)) return 160;
   else if (STRNEQ(file_name, "gradientBar.png", 37)) return 161;
   else if (STRNEQ(file_name, "groundSquareShadow_001.png", 37)) return 162;
   else if (STRNEQ(file_name, "navArrowBtn_001.png", 37)) return 163;
   else if (STRNEQ(file_name, "pit_01_001.png", 37)) return 164;
   else if (STRNEQ(file_name, "pit_02_001.png", 37)) return 165;
   else if (STRNEQ(file_name, "pit_03_001.png", 37)) return 166;
   else if (STRNEQ(file_name, "plank_01_001.png", 37)) return 167;
   else if (STRNEQ(file_name, "plank_01_glow_001.png", 37)) return 168;
   else if (STRNEQ(file_name, "playerSquare_001.png", 37)) return 169;
   else if (STRNEQ(file_name, "player_01_001.png", 37)) return 170;
   else if (STRNEQ(file_name, "player_01_2_001.png", 37)) return 171;
   else if (STRNEQ(file_name, "player_02_001.png", 37)) return 172;
   else if (STRNEQ(file_name, "player_02_2_001.png", 37)) return 173;
   else if (STRNEQ(file_name, "player_03_001.png", 37)) return 174;
   else if (STRNEQ(file_name, "player_03_2_001.png", 37)) return 175;
   else if (STRNEQ(file_name, "player_04_001.png", 37)) return 176;
   else if (STRNEQ(file_name, "player_04_2_001.png", 37)) return 177;
   else if (STRNEQ(file_name, "player_05_001.png", 37)) return 178;
   else if (STRNEQ(file_name, "player_05_2_001.png", 37)) return 179;
   else if (STRNEQ(file_name, "player_06_001.png", 37)) return 180;
   else if (STRNEQ(file_name, "player_06_2_001.png", 37)) return 181;
   else if (STRNEQ(file_name, "player_07_001.png", 37)) return 182;
   else if (STRNEQ(file_name, "player_07_2_001.png", 37)) return 183;
   else if (STRNEQ(file_name, "player_08_001.png", 37)) return 184;
   else if (STRNEQ(file_name, "player_08_2_001.png", 37)) return 185;
   else if (STRNEQ(file_name, "player_09_001.png", 37)) return 186;
   else if (STRNEQ(file_name, "player_09_2_001.png", 37)) return 187;
   else if (STRNEQ(file_name, "player_10_001.png", 37)) return 188;
   else if (STRNEQ(file_name, "player_10_2_001.png", 37)) return 189;
   else if (STRNEQ(file_name, "player_11_001.png", 37)) return 190;
   else if (STRNEQ(file_name, "player_11_2_001.png", 37)) return 191;
   else if (STRNEQ(file_name, "player_12_001.png", 37)) return 192;
   else if (STRNEQ(file_name, "player_12_2_001.png", 37)) return 193;
   else if (STRNEQ(file_name, "player_13_001.png", 37)) return 194;
   else if (STRNEQ(file_name, "player_13_2_001.png", 37)) return 195;
   else if (STRNEQ(file_name, "portal03_front_001.png", 37)) return 196;
   else if (STRNEQ(file_name, "portal_01_back_001.png", 37)) return 197;
   else if (STRNEQ(file_name, "portal_01_front_001.png", 37)) return 198;
   else if (STRNEQ(file_name, "portal_02_back_001.png", 37)) return 199;
   else if (STRNEQ(file_name, "portal_02_front_001.png", 37)) return 200;
   else if (STRNEQ(file_name, "portal_03_back_001.png", 37)) return 201;
   else if (STRNEQ(file_name, "portal_03_front_001.png", 37)) return 202;
   else if (STRNEQ(file_name, "portal_04_back_001.png", 37)) return 203;
   else if (STRNEQ(file_name, "portal_04_front_001.png", 37)) return 204;
   else if (STRNEQ(file_name, "poweredBy_001.png", 37)) return 205;
   else if (STRNEQ(file_name, "ring_01_001.png", 37)) return 206;
   else if (STRNEQ(file_name, "ring_01_glow_001.png", 37)) return 207;
   else if (STRNEQ(file_name, "robtoplogo_small.png", 37)) return 208;
   else if (STRNEQ(file_name, "rod_01_001.png", 37)) return 209;
   else if (STRNEQ(file_name, "rod_02_001.png", 37)) return 210;
   else if (STRNEQ(file_name, "rod_03_001.png", 37)) return 211;
   else if (STRNEQ(file_name, "rod_ball_01_001.png", 37)) return 212;
   else if (STRNEQ(file_name, "rod_ball_02_001.png", 37)) return 213;
   else if (STRNEQ(file_name, "rod_ball_03_001.png", 37)) return 214;
   else if (STRNEQ(file_name, "ship_01_001.png", 37)) return 215;
   else if (STRNEQ(file_name, "spike_01_001.png", 37)) return 216;
   else if (STRNEQ(file_name, "spike_01_glow_001.png", 37)) return 217;
   else if (STRNEQ(file_name, "spike_02_001.png", 37)) return 218;
   else if (STRNEQ(file_name, "spike_02_glow_001.png", 37)) return 219;
   else if (STRNEQ(file_name, "square_01_001.png", 37)) return 220;
   else if (STRNEQ(file_name, "square_01_glow_001.png", 37)) return 221;
   else if (STRNEQ(file_name, "square_02_001.png", 37)) return 222;
   else if (STRNEQ(file_name, "square_02_glow_001.png", 37)) return 223;
   else if (STRNEQ(file_name, "square_03_001.png", 37)) return 224;
   else if (STRNEQ(file_name, "square_03_glow_001.png", 37)) return 225;
   else if (STRNEQ(file_name, "square_04_001.png", 37)) return 226;
   else if (STRNEQ(file_name, "square_04_glow_001.png", 37)) return 227;
   else if (STRNEQ(file_name, "square_05_001.png", 37)) return 228;
   else if (STRNEQ(file_name, "square_06_001.png", 37)) return 229;
   else if (STRNEQ(file_name, "square_06_glow_001.png", 37)) return 230;
   else if (STRNEQ(file_name, "square_07_001.png", 37)) return 231;
   else if (STRNEQ(file_name, "square_07_glow_001.png", 37)) return 232;
   else if (STRNEQ(file_name, "star_001.png", 37)) return 233;
   else if (STRNEQ(file_name, "tutorial_01_001.png", 37)) return 234;
   else if (STRNEQ(file_name, "tutorial_02_001.png", 37)) return 235;
   else if (STRNEQ(file_name, "tutorial_03_001.png", 37)) return 236;
   else if (STRNEQ(file_name, "tutorial_04_001.png", 37)) return 237;
   else if (STRNEQ(file_name, "tutorial_05_001.png", 37)) return 238;
   else if (STRNEQ(file_name, "whiteSquare20_001.png", 37)) return 239;
   else if (STRNEQ(file_name, "whiteSquare40_001.png", 37)) return 240;
   else if (STRNEQ(file_name, "whiteSquare60_001.png", 37)) return 241;
   else if (STRNEQ(file_name, "GJ_GameSheet.png", 37)) return 242;
   else if (STRNEQ(file_name, "GJ_gradientBG.png", 37)) return 243;
   else if (STRNEQ(file_name, "GJ_logo_001.png", 37)) return 244;
   else if (STRNEQ(file_name, "RobTopLogoBig_001.png", 37)) return 245;
   else if (STRNEQ(file_name, "GJ_LaunchSheet.png", 37)) return 246;
   else if (STRNEQ(file_name, "GJ_moveBtn.png", 37)) return 247;
   else if (STRNEQ(file_name, "GJ_moveSBtn.png", 37)) return 248;
   else if (STRNEQ(file_name, "GJ_progressBar_001.png", 37)) return 249;
   else if (STRNEQ(file_name, "GJ_square01.png", 37)) return 250;
   else if (STRNEQ(file_name, "gk-icon.png", 37)) return 251;
   else if (STRNEQ(file_name, "goldFont.png", 37)) return 252;
   else if (STRNEQ(file_name, "gravityOverlay.png", 37)) return 253;
   else if (STRNEQ(file_name, "groundSquare_001.png", 37)) return 254;
   else if (STRNEQ(file_name, "loadingCircle.png", 37)) return 255;
   else if (STRNEQ(file_name, "promo_boom.png", 37)) return 256;
   else if (STRNEQ(file_name, "promo_mm.png", 37)) return 257;
   else if (STRNEQ(file_name, "promo_mu.png", 37)) return 258;
   else if (STRNEQ(file_name, "sliderBar.png", 37)) return 259;
   else if (STRNEQ(file_name, "slidergroove.png", 37)) return 260;
   else if (STRNEQ(file_name, "slidergroove_02.png", 37)) return 261;
   else if (STRNEQ(file_name, "sliderthumb.png", 37)) return 262;
   else if (STRNEQ(file_name, "sliderthumbsel.png", 37)) return 263;
   else if (STRNEQ(file_name, "smallDot.png", 37)) return 264;
   else if (STRNEQ(file_name, "square.png", 37)) return 265;
   else if (STRNEQ(file_name, "square01_001.png", 37)) return 266;
   else if (STRNEQ(file_name, "square02b_001.png", 37)) return 267;
   else if (STRNEQ(file_name, "square02_001.png", 37)) return 268;
   else if (STRNEQ(file_name, "square02_small.png", 37)) return 269;
   else if (STRNEQ(file_name, "square03_001.png", 37)) return 270;
   else if (STRNEQ(file_name, "square04_001.png", 37)) return 271;
   else if (STRNEQ(file_name, "streak.png", 37)) return 272;
   else if (STRNEQ(file_name, "streakDWhite.png", 37)) return 273;
   else if (STRNEQ(file_name, "sun.png", 37)) return 274;
   else return -1;
}

#define RES_PNG(file_name) get_png_id(file_name)
#define MAX_RES_PNG 275

static int get_mp3_id(const char* file_name) {
   if (0) return -1;
   else if (STRNEQ(file_name, "BackOnTrack.mp3", 18)) return 0;
   else if (STRNEQ(file_name, "BaseAfterBase.mp3", 18)) return 1;
   else if (STRNEQ(file_name, "CantLetGo.mp3", 18)) return 2;
   else if (STRNEQ(file_name, "DryOut.mp3", 18)) return 3;
   else if (STRNEQ(file_name, "Jumper.mp3", 18)) return 4;
   else if (STRNEQ(file_name, "menuLoop.mp3", 18)) return 5;
   else if (STRNEQ(file_name, "Polargeist.mp3", 18)) return 6;
   else if (STRNEQ(file_name, "StayInsideMe.mp3", 18)) return 7;
   else if (STRNEQ(file_name, "StereoMadness.mp3", 18)) return 8;
   else return -1;
}

#define RES_MP3(file_name) get_mp3_id(file_name)
#define MAX_RES_MP3 9

static int get_ogg_id(const char* file_name) {
   if (0) return -1;
   else if (STRNEQ(file_name, "achievement_01.ogg", 19)) return 0;
   else if (STRNEQ(file_name, "endStart_02.ogg", 19)) return 1;
   else if (STRNEQ(file_name, "explode_11.ogg", 19)) return 2;
   else if (STRNEQ(file_name, "playSound_01.ogg", 19)) return 3;
   else if (STRNEQ(file_name, "quitSound_01.ogg", 19)) return 4;
   else return -1;
}

#define RES_OGG(file_name) get_ogg_id(file_name)
#define MAX_RES_OGG 5

static int get_fnt_id(const char* file_name) {
   if (0) return -1;
   else if (STRNEQ(file_name, "bigFont.fnt", 13)) return 0;
   else if (STRNEQ(file_name, "chatFont.fnt", 13)) return 1;
   else if (STRNEQ(file_name, "goldFont.fnt", 13)) return 2;
   else return -1;
}

#define RES_FNT(file_name) get_fnt_id(file_name)
#define MAX_RES_FNT 3

static int get_sheet_id(const char* file_name) {
   if (0) return -1;
   else if (STRNEQ(file_name, "CCControlColourPickerSpriteSheet.plist", 39)) return 0;
   else if (STRNEQ(file_name, "GJ_GameSheet.plist", 39)) return 1;
   else if (STRNEQ(file_name, "GJ_LaunchSheet.plist", 39)) return 2;
   else return -1;
}

#define RES_SHEET(file_name) get_sheet_id(file_name)
#define MAX_RES_SHEET 3

static int get_plist_id(const char* file_name) {
   if (0) return -1;
   else if (STRNEQ(file_name, "AchievementsDesc.plist", 24)) return 0;
   else if (STRNEQ(file_name, "bumpEffect.plist", 24)) return 1;
   else if (STRNEQ(file_name, "chargeEffect.plist", 24)) return 2;
   else if (STRNEQ(file_name, "dragEffect.plist", 24)) return 3;
   else if (STRNEQ(file_name, "endEffectPortal.plist", 24)) return 4;
   else if (STRNEQ(file_name, "explodeEffect.plist", 24)) return 5;
   else if (STRNEQ(file_name, "firework.plist", 24)) return 6;
   else if (STRNEQ(file_name, "glitterEffect.plist", 24)) return 7;
   else if (STRNEQ(file_name, "glitterEffectIcon.plist", 24)) return 8;
   else if (STRNEQ(file_name, "landEffect.plist", 24)) return 9;
   else if (STRNEQ(file_name, "levelComplete01.plist", 24)) return 10;
   else if (STRNEQ(file_name, "lvlupEffect.plist", 24)) return 11;
   else if (STRNEQ(file_name, "objectDefinitions.plist", 24)) return 12;
   else if (STRNEQ(file_name, "portalEffect01.plist", 24)) return 13;
   else if (STRNEQ(file_name, "portalEffect02.plist", 24)) return 14;
   else if (STRNEQ(file_name, "portalEffect03.plist", 24)) return 15;
   else if (STRNEQ(file_name, "portalEffect04.plist", 24)) return 16;
   else if (STRNEQ(file_name, "ringEffect.plist", 24)) return 17;
   else if (STRNEQ(file_name, "shipDragEffect.plist", 24)) return 18;
   else if (STRNEQ(file_name, "Skull_w_01.plist", 24)) return 19;
   else if (STRNEQ(file_name, "Skull_w_02.plist", 24)) return 20;
   else if (STRNEQ(file_name, "Skull_w_03.plist", 24)) return 21;
   else if (STRNEQ(file_name, "speedEffect.plist", 24)) return 22;
   else if (STRNEQ(file_name, "starEffect.plist", 24)) return 23;
   else if (STRNEQ(file_name, "starEffect01.plist", 24)) return 24;
   else if (STRNEQ(file_name, "starFall.plist", 24)) return 25;
   else if (STRNEQ(file_name, "stoneHit.plist", 24)) return 26;
   else if (STRNEQ(file_name, "trailEffect.plist", 24)) return 27;
   else return -1;
}

#define RES_PLIST(file_name) get_plist_id(file_name)
#define MAX_RES_PLIST 28
