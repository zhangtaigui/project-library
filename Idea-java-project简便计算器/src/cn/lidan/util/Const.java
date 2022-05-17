package cn.lidan.util;

import java.awt.*;

public class Const {
    public static final int FRAME_W = 400;//窗体宽度
    public static final int FRAME_H = 600;//窗体的高度
    public static final int SCREEN_W = Toolkit.getDefaultToolkit().getScreenSize().width;//屏幕的宽度
    public static final int SCREEN_H = Toolkit.getDefaultToolkit().getScreenSize().height;//屏幕的高度

    public static final int FRAME_X = (SCREEN_W - FRAME_W)/2;
    public static final int FRAME_Y = (SCREEN_H - FRAME_H)/2;

    public static final String TITLE = "简易计算器";
}
