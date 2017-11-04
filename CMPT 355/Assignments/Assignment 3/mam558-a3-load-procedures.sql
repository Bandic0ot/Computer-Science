/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

/* Initial load of the csv files into load tables. */
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
  business_zipcode text,
  business_city text,
  business_state text,
  business_country text,
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

CREATE OR REPLACE FUNCTION load_employees() RETURNS void AS $$
DECLARE
  v_employees RECORD;
  v_employee_id INT;
BEGIN
  FOR v_employees IN
  (SELECT
    CAST(id AS INT),
    first_name,
    last_name,
    gender,
    ssn,
    title,
    middle_name,
    CAST(birthdate AS DATE),
    marital_status,
    home_email
    FROM load_employees)
  LOOP
    SELECT e.id
    INTO v_employee_id
    FROM Employees e
    WHERE e.first_name = v_employees.first_name
    AND e.middle_name = v_employees.middle_name
    AND e.last_name = v_employees.last_name
    AND e.birthdate = v_employees.birthdate
    AND e.ssn = v_employees.ssn;
    IF v_employee_id IS NULL
    THEN
      INSERT INTO Employees(id, first_name, last_name, gender, ssn, title, middle_name, birthdate, marital_status, home_email)
      SELECT
        v.id,
        v.first_name,
        v.last_name,
        v.gender,
        v.ssn,
        v.title,
        v.middle_name,
        v.birthdate,
        v.marital_status,
        v.home_email
      FROM(VALUES (
        v_employees.id,
        v_employees.first_name,
        v_employees.last_name,
        v_employees.gender,
        v_employees.ssn,
        v_employees.title,
        v_employees.middle_name,
        v_employees.birthdate,
        v_employees.marital_status,
        v_employees.home_email))
        AS v (id, first_name, last_name, gender, ssn, title, middle_name, birthdate, marital_status, home_email);
    ELSE
      UPDATE Employees
      SET
        first_name = v_employees.first_name,
        last_name = v_employees.last_name,
        gender = v_employees.gender,
        ssn = v_employees.ssn,
        title = v_employees.title,
        middle_name = v_employees.middle_name,
        birthdate = v_employees.birthdate,
        marital_status = v_employees.marital_status,
        home_email = v_employees.home_email
      WHERE id = v_employee_id;
    END IF;
  END LOOP;
END;
$$ LANGUAGE PLPGSQL;

SELECT load_employees();

CREATE OR REPLACE FUNCTION load_addresses() RETURNS void AS $$
DECLARE
  v_countries RECORD;
  v_provinces RECORD;
  v_cities RECORD;
  v_addresses RECORD;
  v_countries_name text;
  v_provinces_name text;
  v_cities_name text;
  v_address_id INT;
  v_address_type_id INT;
  v_country_id INT;
  v_province_id INT;
  v_city_id INT;
BEGIN
/* ---------- Countries Insert/Update ---------- */
  FOR v_countries IN (SELECT CAST (id AS INT), CAST (home_country AS VARCHAR) AS name FROM load_employees UNION SELECT CAST (id AS INT), business_country FROM load_employees)
  LOOP

    SELECT name
    INTO v_countries_name
    FROM Countries
    WHERE name = v_countries.name;

    IF v_countries_name IS NULL
    THEN
      INSERT INTO Countries(name)
      SELECT v.name
      FROM (VALUES (v_countries.name)) AS v (name);
    ELSE
      UPDATE Countries
      SET name = v_countries.name
      WHERE id = v_countries.id;
    END IF;

  END LOOP;

/* ---------- Provinces Insert/Update ---------- */
  FOR v_provinces IN (SELECT CAST (id AS INT), CAST (home_state AS VARCHAR) AS name FROM load_employees UNION SELECT CAST (id AS INT), business_state FROM load_employees)
  LOOP

    SELECT name
    INTO v_provinces_name
    FROM Provinces
    WHERE name = v_provinces.name;

    IF v_provinces_name IS NULL
    THEN
      INSERT INTO Provinces(name)
      SELECT v.name
      FROM (VALUES (v_provinces.name)) AS v (name);
    ELSE
      UPDATE Provinces
      SET name = v_provinces.name
      WHERE id = v_provinces.id;
    END IF;

  END LOOP;

/* ---------- Cities Insert/Update ---------- */
  FOR v_cities IN (SELECT CAST (id AS INT), CAST (home_city AS VARCHAR) AS name FROM load_employees UNION SELECT CAST (id AS INT), business_city FROM load_employees)
  LOOP

    SELECT name
    INTO v_cities_name
    FROM Cities
    WHERE name = v_cities.name;

    IF v_cities_name IS NULL
    THEN
      INSERT INTO Cities(name)
      SELECT v.name
      FROM (VALUES (v_cities.name)) AS v (name);
    ELSE
      UPDATE Cities
      SET name = v_cities.name
      WHERE id = v_cities.id;
    END IF;
  END LOOP;

/* ---------- Addresses Insert/Update ---------- */
  FOR v_addresses IN
  (SELECT CAST (id AS INT),
  CAST (home_street_number AS INT) AS street_number,
  CAST (home_street_name AS VARCHAR) AS street_name,
  CAST (home_street_suffix AS VARCHAR) AS street_suffix,
  CAST (home_zipcode AS VARCHAR) AS zipcode,
  CAST (home_city AS VARCHAR) AS city,
  CAST (home_state AS VARCHAR) AS state,
  CAST (home_country AS VARCHAR) AS country
  FROM load_employees
  UNION
  SELECT CAST (id AS INT),
  CAST (business_street_number AS INT),
  CAST (business_street_name AS VARCHAR),
  CAST (business_street_suffix AS VARCHAR),
  CAST (business_zipcode AS VARCHAR),
  CAST (business_city AS VARCHAR),
  CAST (business_state AS VARCHAR),
  CAST (business_country AS VARCHAR)
  FROM load_employees)
  LOOP

    SELECT id
    INTO v_address_id
    FROM Addresses
    WHERE street_number = v_addresses.street_number
    AND street_name = v_addresses.street_name
    AND street_suffix = v_addresses.street_suffix
    AND postal_code = v_addresses.zipcode;

    SELECT atype.id
    INTO v_address_type_id
    FROM Address_Types atype, Addresses a
    WHERE atype.id = a.address_type_id;

    IF (
      SELECT 1
      FROM load_employees
      WHERE v_addresses.street_number = CAST (home_street_number AS INT)
      AND v_addresses.street_name = CAST (home_street_name AS VARCHAR)
      AND v_addresses.street_suffix = CAST (home_street_suffix AS VARCHAR)
      AND v_addresses.zipcode = CAST (home_zipcode AS VARCHAR))

    THEN
      SELECT id
      INTO v_address_type_id
      FROM Address_Types
      WHERE type = 'Home';

      /* Set the country ID for the home address. */
      SELECT c.id
      INTO v_country_id
      FROM Countries c
      WHERE v_addresses.country = c.name;

      IF v_country_id IS NULL
      THEN
      RAISE NOTICE 'Country ID: %, not found', v_addresses;
      EXIT;
      END IF;

      /* Set the province ID for the home address. */
      SELECT p.id
      INTO v_province_id
      FROM Provinces p
      WHERE v_addresses.state = p.name;

      IF v_province_id IS NULL
      THEN
      RAISE NOTICE 'Province ID: %, not found', v_addresses;
      EXIT;
      END IF;

      /* Set the city ID for the home address. */
      SELECT c.id
      INTO v_city_id
      FROM Cities c
      WHERE v_addresses.city = c.name;

      IF v_city_id IS NULL
      THEN
      RAISE NOTICE 'City ID: %, not found', v_addresses;
      EXIT;
      END IF;

    ELSEIF (SELECT 1
      FROM load_employees
      WHERE v_addresses.street_number = CAST (business_street_number AS INT)
      AND v_addresses.street_name = CAST (business_street_name AS VARCHAR)
      AND v_addresses.street_suffix = CAST (business_street_suffix AS VARCHAR)
      AND v_addresses.zipcode = CAST (business_zipcode AS VARCHAR))
      THEN
        SELECT id
        INTO v_address_type_id
        FROM Address_Types
        WHERE type = 'Business';

      /* Set the country ID for the business address. */
      SELECT c.id
      INTO v_country_id
      FROM Countries c
      WHERE v_addresses.country = c.name;

      IF v_country_id IS NULL
      THEN
      RAISE NOTICE 'Country ID: %, not found', v_addresses;
      EXIT;
      END IF;

      /* Set the province ID for the business address. */
      SELECT p.id
      INTO v_province_id
      FROM Provinces p
      WHERE v_addresses.state = p.name;

      IF v_province_id IS NULL
      THEN
      RAISE NOTICE 'Province ID: %, not found', v_addresses;
      EXIT;
      END IF;

      /* Set the city ID for the business address. */
      SELECT c.id
      INTO v_city_id
      FROM Cities c
      WHERE v_addresses.city = c.name;

      IF v_city_id IS NULL
      THEN
      RAISE NOTICE 'City ID: %, not found', v_addresses;
      EXIT;
      END IF;

    ELSE
      RAISE NOTICE 'Address type not in range.';
      EXIT;
    END IF;

    IF v_address_id IS NULL
    THEN
      INSERT INTO Addresses(
      street_number,
      street_name,
      street_suffix,
      postal_code,
      city_id,
      province_id,
      country_id,
      address_type_id)
      SELECT
      v.street_number,
      v.street_name,
      v.street_suffix,
      v.postal_code,
      v_city_id,
      v_province_id,
      v_country_id,
      v_address_type_id
      FROM
      (VALUES
      (v_addresses.street_number,
      v_addresses.street_name,
      v_addresses.street_suffix,
      v_addresses.zipcode))
      AS v (street_number, street_name, street_suffix, postal_code);
    ELSE
      UPDATE Addresses
      SET
        street_number = v_addresses.street_number,
        street_name = v_addresses.street_name,
        street_suffix = v_addresses.street_suffix,
        postal_code = v_addresses.zipcode,
        city_id = v_city_id,
        province_id = v_province_id,
        country_id = v_country_id,
        address_type_id = v_address_type_id
      WHERE id = v_addresses.id;
    END IF;

  END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT load_addresses();

CREATE OR REPLACE FUNCTION load_phone_numbers() RETURNS void AS $$
DECLARE
  v_emlpoyees RECORD;
  v_phone_types RECORD;
  v_phone_numbers RECORD;
  v_country_code INT;
  v_area_code INT;
  v_phone_number INT;
  v_extension INT;
  v_phone_id INT;
  v_employee_id INT;
  v_phone_type_id INT;
BEGIN
/* ---------- Addresses Insert/Update ---------- */
  FOR v_phone_numbers IN
  (SELECT CAST (id AS INT),
  CAST (phone1_country_code AS INT) AS country_code,
  CAST (phone1_area_code AS INT) AS area_code,
  CAST (REGEXP_REPLACE(phone1_number, '[-]+', '') AS INT) AS phone_number,
  CAST (phone1_extension AS INT) AS extension,
  CAST (phone1_type AS VARCHAR) AS type
  FROM load_employees
  UNION
  SELECT CAST (id AS INT),
  CAST (phone2_country_code AS INT),
  CAST (phone2_area_code AS INT),
  CAST (REGEXP_REPLACE(phone2_number, '[-]+', '') AS INT),
  CAST (phone2_extension AS INT),
  CAST (phone2_type AS VARCHAR)
  FROM load_employees
  UNION
  SELECT CAST (id AS INT),
  CAST (phone3_country_code AS INT),
  CAST (phone3_area_code AS INT),
  CAST (REGEXP_REPLACE(phone3_number, '[-]+', '') AS INT),
  CAST (phone3_extension AS INT),
  CAST (phone3_type AS VARCHAR)
  FROM load_employees
  UNION
  SELECT CAST (id AS INT),
  CAST (phone4_country_code AS INT),
  CAST (phone4_area_code AS INT),
  CAST (REGEXP_REPLACE(phone4_number, '[-]+', '') AS INT),
  CAST (phone4_extension AS INT),
  CAST (phone4_type AS VARCHAR)
  FROM load_employees)
  LOOP

    SELECT t.id
    INTO v_phone_type_id
    FROM Phone_Types t, Phone_Numbers p
    WHERE p.phone_type_id = t.id;

    SELECT e.id
    INTO v_employee_id
    FROM Employees e, Phone_Numbers p
    WHERE e.id = p.employee_id;

    SELECT id
    INTO v_phone_id
    FROM Phone_Numbers
    WHERE country_code = v_phone_numbers.country_code
    AND area_code = v_phone_numbers.area_code
    AND phone_number = v_phone_numbers.phone_number
    AND extension = v_phone_numbers.extension
    AND employee_id = v_employee_id
    AND phone_type_id = v_phone_type_id;

    IF v_phone_id IS NULL
    THEN
      INSERT INTO Phone_Numbers(country_code, area_code, phone_number, extension, phone_type_id, employee_id)
      SELECT
      p.country_code,
      p.area_code,
      p.phone_number,
      p.extension,
      v_phone_type_id,
      v_employee_id
      FROM (VALUES (
      v_phone_numbers.id,
      v_phone_numbers.country_code,
      v_phone_numbers.area_code,
      v_phone_numbers.phone_number,
      v_phone_numbers.extension)) AS p(id, country_code, area_code, phone_number, extension);
    ELSE
      UPDATE Phone_Numbers
      SET
        country_code = v_phone_numbers.country_code,
        area_code = v_phone_numbers.area_code,
        phone_number = v_phone_numbers.phone_number,
        extension = v_phone_numbers.extension,
        phone_type_id = v_phone_type_id,
        v_employee_id = v_employee_id
      WHERE id = v_phone_numbers.id;
    END IF;
  END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT load_phone_numbers();

INSERT INTO Departments(code, name, manager_code, manager_title)
SELECT d.department_code, d.department_name, CAST(REGEXP_REPLACE(d.manager_code, '[-]+', '') AS INT), d.manager_title
FROM load_department d;

SELECT *
FROM Departments;
END
$$
LANGUAGE plpgsql
