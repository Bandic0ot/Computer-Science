/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

CREATE TABLE Salaries(
  id INT,
  pay_frequency VARCHAR(10),
  pay_type VARCHAR(10),
  PRIMARY KEY (id));

CREATE TABLE Employee_Salary(
  id INT,
  rate FLOAT,
  salary_id INT REFERENCES Salaries,
  PRIMARY KEY (id));

CREATE TABLE Jobs(
  id INT,
  name VARCHAR(50) NOT NULL,
  code VARCHAR(10) UNIQUE NOT NULL,
  effective_date DATE CHECK(effective_date > expire_date),
  expire_date DATE,
  salary_id INT REFERENCES Salaries,
  PRIMARY KEY (id));

CREATE TABLE Employees(
  id INT,
  first_name VARCHAR(50) NOT NULL,
  last_name VARCHAR(50) NOT NULL,
  gender VARCHAR(2) CHECK(gender IN ('M','F','U','NA')),
  ssn INT,
  hire_date DATE,
  termination_date DATE,
  rehire_date DATE,
  job_id INT REFERENCES Jobs,
  employee_salary_id INT REFERENCES Employee_Salary,
  PRIMARY KEY (id));

CREATE TABLE Locations(
  id INT,
  name VARCHAR(50) NOT NULL,
  code VARCHAR(10) UNIQUE NOT NULL,
  PRIMARY KEY (id));

CREATE TABLE Phone_Numbers(
  id INT,
  type VARCHAR(8) CHECK(type IN ('Home', 'Cell', 'Business')),
  number INT,
  PRIMARY KEY (id));

CREATE TABLE Addresses(
  id INT,
  type VARCHAR(8) CHECK(type IN ('Home', 'Business')),
  address VARCHAR(50),
  PRIMARY KEY (id));

CREATE TABLE Employee_Contact(
  id INT,
  employee_id INT REFERENCES Employees,
  phone_number_id INT REFERENCES Phone_Numbers,
  address_id INT REFERENCES Addresses,
  PRIMARY KEY (id));

CREATE TABLE Location_Contact(
  id INT,
  location_id INT REFERENCES Locations,
  phone_number_id INT REFERENCES Phone_Numbers,
  address_id INT REFERENCES Addresses,
  PRIMARY KEY (id));

CREATE TABLE Employee_Location(
  id INT,
  location_id INT REFERENCES Locations,
  employee_id INT REFERENCES Employees,
  PRIMARY KEY (id));

CREATE TABLE Departments(
  id INT,
  name VARCHAR(20),
  code VARCHAR(10) UNIQUE NOT NULL,
  top_position VARCHAR(10),
  location_id INT REFERENCES Locations,
  PRIMARY KEY (id));

CREATE TABLE Employee_Department(
  id INT,
  department_id INT REFERENCES Departments,
  employee_id INT REFERENCES Employees,
  PRIMARY KEY (id));
