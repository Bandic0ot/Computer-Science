INSERT INTO employees(employee_number, title, first_name, middle_name, last_name, gender, ssn, birth_date, marital_status_id, home_email, employment_status_id, hire_date, rehire_date, termination_date, term_type_id, term_reason_id)
VALUES ('888888', 'Mr.', 'John', 'Jacob', 'Jingleheimerschmidt', 'M', '888888888', '1964-01-01', '5', 'jingleheimerschmidt@gmail.com', '1', '2015-01-01', NULL, NULL, NULL, NULL);


UPDATE employees
SET termination_date = '2015-01-02',
    term_type_id = '2',
    term_reason_id = '3'
WHERE employee_number = '100002';


DELETE FROM phone_numbers *
WHERE employee_id = '2';

DELETE FROM employee_reviews *
WHERE employee_id = '2';

DELETE FROM emp_addresses *
WHERE employee_id = '2';

DELETE FROM employee_jobs *
WHERE employee_id = '2';

DELETE FROM employees * 
WHERE employee_number = '100002';


DELETE
FROM employees_audit *;

SELECT set_config('session.trigs_enabled', 'Y', FALSE);