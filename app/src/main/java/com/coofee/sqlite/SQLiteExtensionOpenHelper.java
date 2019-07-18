package com.coofee.sqlite;

import android.content.Context;
import android.util.Log;
import io.requery.android.database.DatabaseErrorHandler;
import io.requery.android.database.sqlite.SQLiteCustomExtension;
import io.requery.android.database.sqlite.SQLiteDatabase;
import io.requery.android.database.sqlite.SQLiteDatabaseConfiguration;
import io.requery.android.database.sqlite.SQLiteOpenHelper;

public abstract class SQLiteExtensionOpenHelper extends SQLiteOpenHelper {
    protected final Context mContext;

    public SQLiteExtensionOpenHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, name, factory, version);
        mContext = context;
    }

    public SQLiteExtensionOpenHelper(Context context, String name, SQLiteDatabase.CursorFactory factory, int version, DatabaseErrorHandler errorHandler) {
        super(context, name, factory, version, errorHandler);
        mContext = context;
    }

    @Override
    protected SQLiteDatabaseConfiguration createConfiguration(String path, int openFlags) {
        SQLiteDatabaseConfiguration configuration = super.createConfiguration(path, openFlags);
        String nativeLibraryDir = mContext.getApplicationInfo().nativeLibraryDir;
        Log.e("SQLiteExtension", "SQLiteExtensionOpenHelper; nativeLibraryDir=" + nativeLibraryDir);
        configuration.customExtensions.add(new SQLiteCustomExtension(nativeLibraryDir + "/libdistance.so", "sqlite3_distance_init"));
        return configuration;
    }
}
