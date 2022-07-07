package com.cyberdaystudio.games.spacecadetpinball;

import android.content.Context;
import android.content.SharedPreferences;

public class HighScoreHandler {

    private static String name_str = "com.cyberdaystudio.games.3dpinball";

    static boolean postHighScore(Context context, int score) {
        SharedPreferences prefs = context.getSharedPreferences(name_str, Context.MODE_PRIVATE);

        int oldscore = prefs.getInt("highscore", 0);
        if (score > oldscore) {
            prefs.edit().putInt("highscore", score).apply();
            return true;
        }
        return false;
    }

    static int getHighScore(Context context) {
        SharedPreferences prefs = context.getSharedPreferences(name_str, Context.MODE_PRIVATE);

        return prefs.getInt("highscore", 0);
    }
}
