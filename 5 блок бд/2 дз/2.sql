CREATE TABLE IF NOT EXISTS жанр (
    ID SERIAL PRIMARY KEY,
    название_жанра VARCHAR(60) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS исполнитель (
    ID SERIAL PRIMARY KEY,
    псевдоним_исполнителя VARCHAR(60) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS исполнитель_жанр (
    исполнитель_id INTEGER REFERENCES исполнитель(ID) ON DELETE CASCADE,
    жанр_id INTEGER REFERENCES жанр(ID) ON DELETE CASCADE,
    PRIMARY KEY (исполнитель_id, жанр_id)
);

CREATE TABLE IF NOT EXISTS альбом (
    ID SERIAL PRIMARY KEY,
    название_альбома VARCHAR(60) NOT NULL,
    год_выпуска INTEGER NOT NULL CHECK (год_выпуска > 1900)
);

CREATE TABLE IF NOT EXISTS исполнитель_альбом (
    исполнитель_id INTEGER REFERENCES исполнитель(ID) ON DELETE CASCADE,
    альбом_id INTEGER REFERENCES альбом(ID) ON DELETE CASCADE,
    PRIMARY KEY (исполнитель_id, альбом_id)
);

CREATE TABLE IF NOT EXISTS трек (
    ID SERIAL PRIMARY KEY,
    название_трека VARCHAR(60) NOT NULL,
    длительность INTEGER NOT NULL CHECK (длительность > 0),
    альбом_id INTEGER NOT NULL REFERENCES альбом(ID) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS сборник (
    ID SERIAL PRIMARY KEY,
    название_сборника VARCHAR(60) NOT NULL,
    год_выпуска INTEGER NOT NULL CHECK (год_выпуска > 1900)
);

CREATE TABLE IF NOT EXISTS трек_сборник (
    трек_id INTEGER REFERENCES трек(ID) ON DELETE CASCADE,
    сборник_id INTEGER REFERENCES сборник(ID) ON DELETE CASCADE,
    PRIMARY KEY (трек_id, сборник_id)
);