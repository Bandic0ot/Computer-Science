/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

CREATE TABLE Address_Types (
  id INT,
  type VARCHAR(50) CHECK (type IN ('Home', 'Business')),
  PRIMARY KEY (id)
);

CREATE TABLE Phone_Types (
  id INT,
  type VARCHAR(50) CHECK (type IN ('Home', 'Mobile', 'Business')),
  PRIMARY KEY (id)
);

CREATE TABLE Countries (
  id INT,
  name VARCHAR(100) UNIQUE,
  PRIMARY KEY (id)
);

CREATE TABLE Provinces (
  id INT,
  name VARCHAR(100) UNIQUE,
  PRIMARY KEY (id)
);

CREATE TABLE Cities (
  id INT,
  name VARCHAR(100) UNIQUE,
  PRIMARY KEY (id)
);

CREATE TABLE Addresses (
  id INT,
  address_type VARCHAR(10),
  street_number INT,
  street_name VARCHAR(50),
  street_suffix VARCHAR(10),
  postal_code VARCHAR(10),
  address_type_id INT REFERENCES Address_Types,
  city_id INT REFERENCES Cities,
  province_id INT REFERENCES Provinces,
  country_id INT REFERENCES Countries,
  PRIMARY KEY (id)
);

CREATE TABLE Phone_Numbers (
  id INT,
  country_code INT,
  area_code INT,
  phone_number INT,
  extension INT,
  phone_type_id INT REFERENCES Phone_Types,
  PRIMARY KEY (id)
);

CREATE TABLE Employees (
  id INT,
  first_name VARCHAR(50),
  last_name VARCHAR(50),
  gender VARCHAR(10),
  ssn INT,
  PRIMARY KEY (id)
);

CREATE TABLE Locations (
  id INT,
  code VARCHAR(10) UNIQUE,
  name VARCHAR(50),
  address_id INT REFERENCES Addresses,
  PRIMARY KEY (id)
);

CREATE TABLE Employee_Contact (
  id INT,
  employee_id INT REFERENCES Employees,
  phone_number_id INT REFERENCES Phone_Numbers,
  address_id INT REFERENCES Addresses,
  PRIMARY KEY (id)
);

CREATE TABLE Employee_Location (
  id INT,
  location_id INT REFERENCES Locations,
  employee_id INT REFERENCES Employees,
  PRIMARY KEY (id)
);

CREATE TABLE Departments (
  id INT,
  code VARCHAR(10) UNIQUE,
  name VARCHAR(20),
  location_id INT REFERENCES Locations,
  PRIMARY KEY (id)
);

CREATE TABLE Employee_Department (
  id INT,
  department_id INT REFERENCES Departments,
  employee_id INT REFERENCES Employees,
  PRIMARY KEY (id)
);

CREATE TABLE Jobs (
  id INT,
  code VARCHAR(10) UNIQUE,
  name VARCHAR(50),
  effective_date DATE CHECK(effective_date > expire_date),
  expire_date DATE,
  pay_frequency VARCHAR(10),
  pay_type VARCHAR(10),
  report_to_job_id INT REFERENCES Jobs,
  department_id INT REFERENCES Departments,
  PRIMARY KEY (id)
);

CREATE TABLE Employee_Jobs (
  id INT,
  hire_date DATE,
  rehire_date DATE,
  hourly_amount FLOAT,
  salary_amount FLOAT,
  employee_id INT REFERENCES Employees,
  job_id INT REFERENCES Jobs,
  PRIMARY KEY (id)
);

ALTER TABLE Departments
ADD COLUMN manager_job_id INT REFERENCES Jobs;
