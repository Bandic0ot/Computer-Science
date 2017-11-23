/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

DROP VIEW IF EXISTS report_view;

CREATE OR REPLACE VIEW report_view
  AS
  SELECT
    e.employee_number AS emplid,
    e.title,
    e.first_name AS firstName,
    e.middle_name AS middleName,
    e.last_name AS lastName,
    CASE UPPER(e.gender)
      WHEN 'M' THEN 'Male'
      WHEN 'F' THEN 'Female'
      ELSE 'U'
    END AS gender,
    e.birth_date AS birthdate,
    m.name AS maritalStatus,
    REGEXP_REPLACE(e.ssn, '(\d{3})(\d{2})(\d{4})', '\1-\2-\3') AS SSN,
    e.home_email AS homeEmail,
    e.hire_date AS OrigHireDate,
    e.rehire_date AS rehireDate,
    e.termination_date AS termDate,
    tt.name AS termType,
    tr.name AS termReason,
    j.name AS jobTitle,
    j.code AS jobCode,
    j.effective_date AS jobStartDt,
    j.expiry_date AS jobEndDt,
    d.code AS departmentCode,
    l.code AS locationCode,
    pf.name AS payFreq,
    pt.name AS payType,
    (SELECT TO_CHAR(pa.pay_amount, 'FM$99G999G999.00') FROM employee_jobs pa
    WHERE pa.employee_id = e.id AND pa.pay_amount < '100')  AS hourlyAmount,
    (SELECT TO_CHAR(pa.pay_amount, 'FM$99G999G999.00') FROM employee_jobs pa
    WHERE pa.employee_id = e.id AND pa.pay_amount > '100')  AS salaryAmount,
    su.code AS supervisorJobCode,
    es.name AS employeeStatus,
    ej.standard_hours AS standardHours,
    et.name AS employeeType,
    est.name AS employmentStatusType,
    rr.id AS lastPerformanceRating,
    rr.review_text AS lastPerformanceRatingText,
    er.review_date AS lastPerformanceRatingDate,
    (SELECT SUBSTRING(emp_address.street, '^([\w\-]+)')) AS homeStreetNum,
    (SELECT SUBSTRING(emp_address.street, '(?<= )(.*)(?= )')) AS homeStreetName,
    (SELECT SUBSTRING(emp_address.street, '\s([\w\-]+)$')) AS homeStreetSuffix,
    emp_address.city AS homeCity,
    emp_prov.name AS homeState,
    emp_country.name AS homeCountry,
    emp_address.postal_code AS homeZipCode,
    (SELECT SUBSTRING(bus_address.street, '^([\w\-]+)')) AS busStreetNum,
    (SELECT SUBSTRING(bus_address.street, '(?<= )(.*)(?= )')) AS busStreetName,
    (SELECT SUBSTRING(bus_address.street, '\s([\w\-]+)$')) AS busStreetSuffix,
    bus_address.postal_code AS busZipCode,
    bus_address.city AS busCity,
    bus_prov.name AS busState,
    bus_country.name AS busCountry,
    (SELECT p.country_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 0) AS phone1CountryCode,
    (SELECT p.area_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 0) AS phone1AreaCode,
    (SELECT p.ph_number FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 0) AS phone1Number,
    (SELECT p.extension FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 0) AS phone1Extension,
    (SELECT pt.name FROM phone_types pt, phone_numbers p  WHERE pt.id = p.type_id AND p.employee_id = e.id LIMIT 1 OFFSET 0) AS phone1Type,
    (SELECT p.country_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 1) AS phone2CountryCode,
    (SELECT p.area_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 1) AS phone2AreaCode,
    (SELECT REGEXP_REPLACE(p.ph_number, '(\d{3})(\d{4})', '\1-\2')
    FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 1) AS phone2Number,
    (SELECT p.extension FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 1) AS phone2Extension,
    (SELECT pt.name FROM phone_types pt, phone_numbers p  WHERE pt.id = p.type_id AND p.employee_id = e.id LIMIT 1 OFFSET 1) AS phone2Type,
    (SELECT p.country_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 2) AS phone3CountryCode,
    (SELECT p.area_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 2) AS phone3AreaCode,
    (SELECT REGEXP_REPLACE(p.ph_number, '(\d{3})(\d{4})', '\1-\2')
    FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 2) AS phone3Number,
    (SELECT p.extension FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 2) AS phone3Extension,
    (SELECT pt.name FROM phone_types pt, phone_numbers p  WHERE pt.id = p.type_id AND p.employee_id = e.id LIMIT 1 OFFSET 3) AS phone3Type,
    (SELECT p.country_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 3) AS phone4CountryCode,
    (SELECT p.area_code FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 3) AS phone4AreaCode,
    (SELECT REGEXP_REPLACE(p.ph_number, '(\d{3})(\d{4})', '\1-\2')
    FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 3) AS phone4Number,
    (SELECT p.extension FROM phone_numbers p WHERE p.employee_id = e.id LIMIT 1 OFFSET 3) AS phone4Extension,
    (SELECT pt.name FROM phone_types pt, phone_numbers p  WHERE pt.id = p.type_id AND p.employee_id = e.id LIMIT 1 OFFSET 4) AS phone4Type
    FROM employees e
    JOIN marital_statuses m ON e.marital_status_id = m.id
    JOIN employee_jobs ej ON ej.employee_id = e.id
    JOIN employee_statuses es ON ej.employee_status_id = es.id
    JOIN jobs j ON ej.job_id = j.id
    JOIN employee_types et ON ej.employee_type_id = et.id
    JOIN departments d ON j.department_id = d.id
    JOIN locations l ON d.location_id = l.id
    JOIN pay_frequencies pf ON j.pay_frequency_id = pf.id
    JOIN pay_types pt ON j.pay_type_id = pt.id
    JOIN employee_reviews er ON er.employee_id = e.id
    JOIN review_ratings rr ON er.rating_id = rr.id
    JOIN emp_addresses emp_address ON emp_address.employee_id = e.id AND emp_address.type_id = '1'
    JOIN emp_addresses bus_address ON bus_address.employee_id = e.id AND bus_address.type_id = '2'
    JOIN provinces emp_prov ON emp_address.province_id = emp_prov.id
    JOIN provinces bus_prov ON bus_address.province_id = bus_prov.id
    JOIN countries emp_country ON emp_address.country_id = emp_country.id
    JOIN countries bus_country ON bus_address.country_id = bus_country.id
    LEFT JOIN employment_status_types est ON e.employment_status_id = est.id
    LEFT JOIN termination_reasons tr ON e.term_reason_id = tr.id
    LEFT JOIN termination_types tt ON e.term_type_id = tt.id
    LEFT JOIN jobs su ON j.supervisor_job_id = su.id;
