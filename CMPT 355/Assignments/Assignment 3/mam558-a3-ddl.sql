/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

/* Create new tables based on new information provided by organization. */
CREATE TABLE Employee_Performance (
  id SERIAL,
  last_rating INT,
  last_rating_text VARCHAR(1000),
  last_rating_date DATE,
  employee_jobs_id INT REFERENCES Employee_Jobs,
  PRIMARY KEY(id)
);

CREATE TABLE Employee_Termination (
  id SERIAL,
  termination_date DATE,
  termination_reason VARCHAR(50),
  termination_type VARCHAR(50),
  employee_jobs_id INT REFERENCES Employee_Jobs,
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
ADD COLUMN employee_status VARCHAR(50),
ADD COLUMN employee_type VARCHAR(20),
ADD COLUMN active_status VARCHAR(20);

/* Alter existing table data types to match organizations data. */
ALTER TABLE Employees
ALTER COLUMN ssn TYPE VARCHAR(20);

/* Alter existing table IDs to auto-increment. */
/* Giving ownership to the table so that if we drop the table the */
/* sequence gets dropped as well. */
/* NOTE: No sequence was created for employees because their IDs */
/* are given by the organization. */
CREATE SEQUENCE address_types_id_seq;
ALTER SEQUENCE address_types_id_seq OWNED BY Address_Types.id;
ALTER TABLE Address_Types ALTER COLUMN id SET DEFAULT nextval('address_types_id_seq');

CREATE SEQUENCE phone_types_id_seq;
ALTER SEQUENCE phone_types_id_seq OWNED BY Phone_Types.id;
ALTER TABLE Phone_Types ALTER COLUMN id SET DEFAULT nextval('phone_types_id_seq');

CREATE SEQUENCE countries_id_seq;
ALTER SEQUENCE countries_id_seq OWNED BY Countries.id;
ALTER TABLE Countries ALTER COLUMN id SET DEFAULT nextval('countries_id_seq');

CREATE SEQUENCE provinces_id_seq;
ALTER SEQUENCE provinces_id_seq OWNED BY Provinces.id;
ALTER TABLE Provinces ALTER COLUMN id SET DEFAULT nextval('provinces_id_seq');

CREATE SEQUENCE cities_id_seq;
ALTER SEQUENCE cities_id_seq OWNED BY Cities.id;
ALTER TABLE Cities ALTER COLUMN id SET DEFAULT nextval('cities_id_seq');

CREATE SEQUENCE addresses_id_seq;
ALTER SEQUENCE addresses_id_seq OWNED BY Addresses.id;
ALTER TABLE Addresses ALTER COLUMN id SET DEFAULT nextval('addresses_id_seq');

CREATE SEQUENCE phone_numbers_id_seq;
ALTER SEQUENCE phone_numbers_id_seq OWNED BY Phone_Numbers.id;
ALTER TABLE Phone_Numbers ALTER COLUMN id SET DEFAULT nextval('phone_numbers_id_seq');

CREATE SEQUENCE locations_id_seq;
ALTER SEQUENCE locations_id_seq OWNED BY Locations.id;
ALTER TABLE Locations ALTER COLUMN id SET DEFAULT nextval('locations_id_seq');

CREATE SEQUENCE employee_addresses_id_seq;
ALTER SEQUENCE employee_addresses_id_seq OWNED BY Employee_Addresses.id;
ALTER TABLE Employee_Addresses ALTER COLUMN id SET DEFAULT nextval('employee_addresses_id_seq');

CREATE SEQUENCE employee_locations_id_seq;
ALTER SEQUENCE employee_locations_id_seq OWNED BY Employee_Locations.id;
ALTER TABLE Employee_Locations ALTER COLUMN id SET DEFAULT nextval('employee_locations_id_seq');

CREATE SEQUENCE departments_id_seq;
ALTER SEQUENCE departments_id_seq OWNED BY Departments.id;
ALTER TABLE Departments ALTER COLUMN id SET DEFAULT nextval('departments_id_seq');

CREATE SEQUENCE employee_departments_id_seq;
ALTER SEQUENCE employee_departments_id_seq OWNED BY Employee_Departments.id;
ALTER TABLE Employee_Departments ALTER COLUMN id SET DEFAULT nextval('employee_departments_id_seq');

CREATE SEQUENCE jobs_id_seq;
ALTER SEQUENCE jobs_id_seq OWNED BY Jobs.id;
ALTER TABLE Jobs ALTER COLUMN id SET DEFAULT nextval('jobs_id_seq');

CREATE SEQUENCE employee_jobs_id_seq;
ALTER SEQUENCE employee_jobs_id_seq OWNED BY Employee_Jobs.id;
ALTER TABLE Employee_Jobs ALTER COLUMN id SET DEFAULT nextval('employee_jobs_id_seq');

CREATE SEQUENCE managers_id_seq;
ALTER SEQUENCE managers_id_seq OWNED BY Managers.id;
ALTER TABLE Managers ALTER COLUMN id SET DEFAULT nextval('managers_id_seq');

/* Populate the small tables */
INSERT INTO Phone_Types (id, type)
VALUES (1, 'Home'), (2, 'Business'), (3, 'Mobile');

INSERT INTO Address_Types (id, type)
VALUES (1, 'Home'), (2, 'Business');
