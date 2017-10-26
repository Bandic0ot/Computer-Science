/* Initial load of the csv files into tables. */
CREATE TABLE IF NOT EXISTS load_employees (
  id text,
  title text,
  first_name text,
  middle_name text,
  last_name text,
  gender text,
  birthdate text,
  marital_status text,
  ssn text,
  home_email text,
  hire_date text,
  rehire_date text,
  termination_date text,
  termination_type text,
  termination_reason text,
  job_title text,
  job_code text,
  job_start_date text,
  job_end_date text,
  department_code text,
  location_code text,
  pay_frequency text,
  pay_type text,
  hourly_amount text,
  salary_amount text,
  supervisor_code text,
  employee_status text,
  standard_hours text,
  employee_type text,
  employment_status text,
  performance_rating text,
  performance_rating_text text,
  performance_rating_date text,
  home_street_number text,
  home_street_name text,
  home_street_suffix text,
  home_city text,
  home_state text,
  home_country text,
  home_zipcode text,
  business_street_number text,
  business_street_name text,
  business_street_suffix text,
  business_city text,
  business_state text,
  business_country text,
  business_zipcode text,
  phone1_country_code text,
  phone1_area_code text,
  phone1_number text,
  phone1_extension text,
  phone1_type text,
  phone2_country_code text,
  phone2_area_code text,
  phone2_number text,
  phone2_extension text,
  phone2_type text,
  phone3_country_code text,
  phone3_area_code text,
  phone3_number text,
  phone3_extension text,
  phone3_type text,
  phone4_country_code text,
  phone4_area_code text,
  phone4_number text,
  phone4_extension text,
  phone4_type text
);

CREATE TABLE IF NOT EXISTS load_location (
  location_code text,
  location_name text,
  street text,
  city text,
  province text,
  country text,
  zipcode text
);

CREATE TABLE IF NOT EXISTS load_department (
  department_code text,
  department_name text,
  manager_code text,
  manager_title text,
  effective_date text,
  expire_date text
);

CREATE TABLE IF NOT EXISTS load_job (
  job_code text,
  job_name text,
  effective_date text,
  expire_date text
);

CREATE FUNCTION load_function()
RETURNS void AS
$$
DECLARE
num_departments RECORD;
id_incrementer SEQUENCE;
BEGIN
INSERT INTO Phone_Types (id, type)
VALUES (1, 'Home'), (2, 'Business'), (3, 'Mobile');

INSERT INTO Address_Types (id, type)
VALUES (1, 'Home'), (2, 'Business');

INSERT INTO Cities
SELECT e.home_city, e.business_city
FROM load_employees e;

/* Begin parsing the loaded tables */
INSERT INTO Employees(title, first_name, middle_name, last_name, gender, birthdate, marital_status, home_email, ssn)
SELECT e.title, e.first_name, e.middle_name, e.last_name, e.gender, e.birthdate, e.marital_status, e.home_email, e.ssn
FROM load_employees e;

INSERT INTO Departments(code, name, manager_code, manager_title)
SELECT d.department_code, d.department_name, CAST(REGEXP_REPLACE(d.manager_code, '[-]+', '') AS INT), d.manager_title
FROM load_department d;

SELECT *
FROM Departments;
END;
$$
LANGUAGE plpgsql
