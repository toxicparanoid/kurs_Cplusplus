CREATE TABLE employee (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    place VARCHAR(100) NOT NULL,
    chief_id INTEGER,
    FOREIGN KEY (chief_id) REFERENCES employee(id)
);