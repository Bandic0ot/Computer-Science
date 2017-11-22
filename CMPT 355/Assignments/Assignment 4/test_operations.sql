/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

SELECT set_config('session.trigs_enabled', 'Y', FALSE);

INSERT INTO employees(employee_number, title, first_name, middle_name, last_name, gender, ssn, birth_date, marital_status_id, home_email, employment_status_id, hire_date, rehire_date, termination_date, term_type_id, term_reason_id)
VALUES ('888888', 'Mr.', 'John', 'Jacob', 'Jingleheimerschmidt', 'M', '88888889', '1964-01-01', '5', 'jingleheimerschmidt@gmail.com', '1', '2015-01-01', NULL, NULL, NULL, NULL);

INSERT INTO employee_jobs(employee_id, job_id, effective_date, expiry_date, pay_amount, standard_hours, employee_type_id, employee_status_id)
VALUES ('953', '14', '2015-01-01', NULL, '100000', '40', '2', '1');

UPDATE employees
SET marital_status_id = '3'
WHERE employee_number = '888888';

UPDATE employee_jobs
SET pay_amount = '20000'
WHERE employee_id = '953';

UPDATE employees
SET marital_status_id = '4'
WHERE employee_number = '888888';

UPDATE employee_jobs
SET pay_amount = '77034'
WHERE employee_id = '953';
