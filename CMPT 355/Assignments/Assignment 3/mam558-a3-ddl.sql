/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

/* Create new tables */
CREATE TABLE Employee_Performance (
  id INT,
  last_rating INT,
  last_rating_text VARCHAR(1000),
  last_rating_date DATE,
  employee_id INT REFERENCES Employees,
  PRIMARY KEY(id)
);

CREATE TABLE Employee_Termination (
  id INT,
  termination_date DATE,
  termination_reason VARCHAR(50),
  termination_type VARCHAR(50),
  employee_id INT REFERENCES Employees,
  PRIMARY KEY(id)
);

/* Alter existing tables based on new information provided by organization. */
ALTER TABLE Employees
ADD COLUMN title VARCHAR(10),
ADD COLUMN middle_name VARCHAR(50),
ADD COLUMN birthdate DATE,
ADD COLUMN marital_status VARCHAR(20),
ADD COLUMN home_email VARCHAR(50);

ALTER TABLE Employee_Jobs
ADD COLUMN standard_hours INT,
ADD COLUMN employee_activity VARCHAR(50),
ADD COLUMN employee_type VARCHAR(20),
ADD COLUMN employee_status VARCHAR(20);

/* Alter existing table types to allow for proper amount of data. */
CREATE SEQUENCE department_id_incrementer;

ALTER TABLE Departments ALTER COLUMN id SET DEFAULT nextval('department_id_incrementer');
ALTER TABLE Departments ALTER COLUMN name TYPE VARCHAR(50);
