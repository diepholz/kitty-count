DROP TABLE IF EXISTS user;
DROP TABLE IF EXISTS counts;

CREATE TABLE user (
    id INTEGER primary KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL
);

CREATE TABLE visits (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    visits INTEGER NOT NULL,
    time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);