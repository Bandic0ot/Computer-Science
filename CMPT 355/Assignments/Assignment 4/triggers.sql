/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

/* Create audit trigger function for employees table. */
CREATE OR REPLACE FUNCTION employees_audit_trigger()
RETURNS TRIGGER AS $$
DECLARE
  v_trig_enabled VARCHAR(1);
BEGIN
  SELECT COALESCE(current_setting('session.trigs_enabled'), 'Y')
  INTO v_trig_enabled;

  IF v_trig_enabled = 'Y' THEN
    IF(TG_OP = 'DELETE') THEN
      INSERT INTO employees_audit (
        employee_number,
        title,
        first_name,
        middle_name,
        last_name,
        gender,
        ssn,
        birth_date,
        marital_status_id,
        home_email,
        employment_status_id,
        hire_date,
        rehire_date,
        termination_date,
        term_type_id,
        term_reason_id,
        audit_date,
        audit_action,
        audit_user
      )
      VALUES (
        OLD.employee_number,
        OLD.title,
        OLD.first_name,
        OLD.middle_name,
        OLD.last_name,
        OLD.gender,
        OLD.ssn,
        OLD.birth_date,
        OLD.marital_status_id,
        OLD.home_email,
        OLD.employment_status_id,
        OLD.hire_date,
        OLD.rehire_date,
        OLD.termination_date,
        OLD.term_type_id,
        OLD.term_reason_id,
        CURRENT_TIMESTAMP,
        'Delete',
        user
      );
      RETURN OLD;
    ELSEIF(TG_OP = 'UPDATE') THEN
      INSERT INTO employees_audit (
        employee_number,
        title,
        first_name,
        middle_name,
        last_name,
        gender,
        ssn,
        birth_date,
        marital_status_id,
        home_email,
        employment_status_id,
        hire_date,
        rehire_date,
        termination_date,
        term_type_id,
        term_reason_id,
        audit_date,
        audit_action,
        audit_user
      )
      VALUES (
        NEW.employee_number,
        NEW.title,
        NEW.first_name,
        NEW.middle_name,
        NEW.last_name,
        NEW.gender,
        NEW.ssn,
        NEW.birth_date,
        NEW.marital_status_id,
        NEW.home_email,
        NEW.employment_status_id,
        NEW.hire_date,
        NEW.rehire_date,
        NEW.termination_date,
        NEW.term_type_id,
        NEW.term_reason_id,
        CURRENT_TIMESTAMP,
        'Update',
        user
      );
      RETURN NEW;
    ELSEIF(TG_OP = 'INSERT') THEN
      INSERT INTO employees_audit (
        employee_number,
        title,
        first_name,
        middle_name,
        last_name,
        gender,
        ssn,
        birth_date,
        marital_status_id,
        home_email,
        employment_status_id,
        hire_date,
        rehire_date,
        termination_date,
        term_type_id,
        term_reason_id,
        audit_date,
        audit_action,
        audit_user
      )
      VALUES (
        NEW.employee_number,
        NEW.title,
        NEW.first_name,
        NEW.middle_name,
        NEW.last_name,
        NEW.gender,
        NEW.ssn,
        NEW.birth_date,
        NEW.marital_status_id,
        NEW.home_email,
        NEW.employment_status_id,
        NEW.hire_date,
        NEW.rehire_date,
        NEW.termination_date,
        NEW.term_type_id,
        NEW.term_reason_id,
        CURRENT_TIMESTAMP,
        'Insert',
        user
      );
      RETURN NEW;
    END IF;
  END IF;
  RETURN NULL;
END;
$$ LANGUAGE plpgsql;

/* Create audit trigger for employees table. */
CREATE TRIGGER c_employees_audit_trigger
AFTER INSERT OR UPDATE OR DELETE ON employees
FOR EACH ROW
EXECUTE PROCEDURE employees_audit_trigger();

/* Create audit trigger function for employee_jobs table. */
CREATE OR REPLACE FUNCTION employee_jobs_audit_trigger()
RETURNS TRIGGER AS $$
DECLARE
  v_trig_enabled VARCHAR(1);
BEGIN
  SELECT COALESCE(current_setting('session.trigs_enabled'), 'Y')
  INTO v_trig_enabled;

  IF v_trig_enabled = 'Y' THEN
    IF(TG_OP = 'DELETE') THEN
      INSERT INTO employee_jobs_audit (
        employee_id,
        job_id,
        effective_date,
        expiry_date,
        pay_amount,
        standard_hours,
        employee_type_id,
        employee_status_id,
        audit_date,
        audit_action,
        audit_user
      )
      VALUES (
        OLD.employee_id,
        OLD.job_id,
        OLD.effective_date,
        OLD.expiry_date,
        OLD.pay_amount,
        OLD.standard_hours,
        OLD.employee_type_id,
        OLD.employee_status_id,
        CURRENT_TIMESTAMP,
        'Delete',
        user
      );
      RETURN OLD;
    ELSEIF(TG_OP = 'UPDATE') THEN
      INSERT INTO employee_jobs_audit (
        employee_id,
        job_id,
        effective_date,
        expiry_date,
        pay_amount,
        standard_hours,
        employee_type_id,
        employee_status_id,
        audit_date,
        audit_action,
        audit_user
      )
      VALUES (
        NEW.employee_id,
        NEW.job_id,
        NEW.effective_date,
        NEW.expiry_date,
        NEW.pay_amount,
        NEW.standard_hours,
        NEW.employee_type_id,
        NEW.employee_status_id,
        CURRENT_TIMESTAMP,
        'Update',
        user
      );
      RETURN NEW;
    ELSEIF(TG_OP = 'INSERT') THEN
      INSERT INTO employee_jobs_audit (
        employee_id,
        job_id,
        effective_date,
        expiry_date,
        pay_amount,
        standard_hours,
        employee_type_id,
        employee_status_id,
        audit_date,
        audit_action,
        audit_user
      )
      VALUES (
        NEW.employee_id,
        NEW.job_id,
        NEW.effective_date,
        NEW.expiry_date,
        NEW.pay_amount,
        NEW.standard_hours,
        NEW.employee_type_id,
        NEW.employee_status_id,
        CURRENT_TIMESTAMP,
        'Insert',
        user
      );
      RETURN NEW;
    END IF;
  END IF;
  RETURN NULL;
END;
$$ LANGUAGE plpgsql;

/* Create audit trigger for employee_jobs table. */
CREATE TRIGGER c_employee_jobs_audit_trigger
AFTER INSERT OR UPDATE OR DELETE ON employee_jobs
FOR EACH ROW
EXECUTE PROCEDURE employee_jobs_audit_trigger();


/* Create history trigger function for employees table. */
CREATE OR REPLACE FUNCTION employee_history_trigger()
RETURNS TRIGGER AS $$
DECLARE
  v_trig_enabled VARCHAR(1);
BEGIN
  SELECT COALESCE(current_setting('session.trigs_enabled'), 'Y')
  INTO v_trig_enabled;

  IF v_trig_enabled = 'Y' THEN
    IF(TG_OP = 'UPDATE') THEN
      INSERT INTO employee_history (
        employee_number,
        title,
        first_name,
        middle_name,
        last_name,
        gender,
        ssn,
        birth_date,
        marital_status_code,
        marital_status_name,
        employee_status_code,
        employee_status_name,
        orig_hire_date,
        rehire_date,
        termination_date,
        termination_reason_code,
        termination_reason_name,
        termination_type_code,
        termination_type_name,
        job_code,
        job_title,
        job_st_date,
        job_end_date,
        pay_amount,
        standard_hours,
        employee_type_code,
        employee_type_name,
        employment_status_code,
        employment_status_name,
        department_code,
        department_name,
        location_code,
        location_name,
        pay_frequency_code,
        pay_frequency_name,
        pay_type_code,
        pay_type_name,
        supervisor_job_code,
        supervisor_job_title,
        history_timestamp
      )
      VALUES (
        NEW.employee_number,
        NEW.title,
        NEW.first_name,
        NEW.middle_name,
        NEW.last_name,
        NEW.gender,
        NEW.ssn,
        NEW.birth_date,

        (SELECT m.code
          FROM marital_statuses m
          WHERE m.id = NEW.marital_status_id),

        (SELECT m.name
          FROM marital_statuses m
          WHERE m.id = NEW.marital_status_id),

        (SELECT e.employee_status_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.employee_status_name
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        NEW.hire_date,
        NEW.rehire_date,
        NEW.termination_date,

        (SELECT t.code
          FROM termination_reasons t
          WHERE t.id = NEW.term_reason_id),

        (SELECT t.name
          FROM termination_reasons t
          WHERE t.id = NEW.term_reason_id),

        (SELECT t.code
          FROM termination_types t
          WHERE t.id = NEW.term_type_id),

        (SELECT t.name
          FROM termination_types t
          WHERE t.id = NEW.term_type_id),

        (SELECT e.job_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.job_title
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.job_st_date
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.job_end_date
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.pay_amount
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.standard_hours
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.employee_type_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.employee_type_name
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.code
          FROM employment_status_types e
          WHERE e.id = NEW.employment_status_id),

        (SELECT e.name
          FROM employment_status_types e
          WHERE e.id = NEW.employment_status_id),

        (SELECT e.department_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.department_name
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.location_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.location_name
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.pay_frequency_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.pay_frequency_name
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.pay_type_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.pay_type_name
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.supervisor_job_code
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        (SELECT e.supervisor_job_title
          FROM employee_history e
          WHERE e.employee_number = NEW.employee_number),

        CURRENT_TIMESTAMP
      );
      RETURN NEW;
    ELSEIF(TG_OP = 'DELETE') THEN
      INSERT INTO employee_history (
        employee_number,
        title,
        first_name,
        middle_name,
        last_name,
        gender,
        ssn,
        birth_date,
        marital_status_code,
        marital_status_name,
        employee_status_code,
        employee_status_name,
        orig_hire_date,
        rehire_date,
        termination_date,
        termination_reason_code,
        termination_reason_name,
        termination_type_code,
        termination_type_name,
        job_code,
        job_title,
        job_st_date,
        job_end_date,
        pay_amount,
        standard_hours,
        employee_type_code,
        employee_type_name,
        employment_status_code,
        employment_status_name,
        department_code,
        department_name,
        location_code,
        location_name,
        pay_frequency_code,
        pay_frequency_name,
        pay_type_code,
        pay_type_name,
        supervisor_job_code,
        supervisor_job_title,
        history_timestamp
      )
      VALUES (
        OLD.employee_number,
        OLD.title,
        OLD.first_name,
        OLD.middle_name,
        OLD.last_name,
        OLD.gender,
        OLD.ssn,
        OLD.birth_date,

        (SELECT m.code
          FROM marital_statuses m
          WHERE m.id = OLD.marital_status_id),

        (SELECT m.name
          FROM marital_statuses m
          WHERE m.id = OLD.marital_status_id),

        (SELECT e.employee_status_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.employee_status_name
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        OLD.hire_date,
        OLD.rehire_date,
        OLD.termination_date,

        (SELECT t.code
          FROM termination_reasons t
          WHERE t.id = OLD.term_reason_id),

        (SELECT t.name
          FROM termination_reasons t
          WHERE t.id = OLD.term_reason_id),

        (SELECT t.code
          FROM termination_types t
          WHERE t.id = OLD.term_type_id),

        (SELECT t.name
          FROM termination_types t
          WHERE t.id = OLD.term_type_id),

        (SELECT e.job_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.job_title
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.job_st_date
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.job_end_date
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.pay_amount
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.standard_hours
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.employee_type_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.employee_type_name
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.code
          FROM employment_status_types e
          WHERE e.id = OLD.employment_status_id),

        (SELECT e.name
          FROM employment_status_types e
          WHERE e.id = OLD.employment_status_id),

        (SELECT e.department_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.department_name
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.location_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.location_name
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.pay_frequency_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.pay_frequency_name
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.pay_type_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.pay_type_name
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.supervisor_job_code
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        (SELECT e.supervisor_job_title
          FROM employee_history e
          WHERE e.employee_number = OLD.employee_number),

        CURRENT_TIMESTAMP
      );
      RETURN OLD;
    END IF;
  END IF;
  RETURN NULL;
END;
$$ LANGUAGE plpgsql;

/* Create history update trigger for employees table. */
CREATE TRIGGER b_employee_history_update_trigger
AFTER UPDATE ON employees
FOR EACH ROW WHEN(OLD.* != NEW.*)
EXECUTE PROCEDURE employee_history_trigger();


/* Create history delete trigger for employees table. */
CREATE TRIGGER a_employee_history_delete_trigger
AFTER DELETE ON employees
FOR EACH ROW
WHEN(OLD.* IS NOT NULL)
EXECUTE PROCEDURE employee_history_trigger();


/* Create history trigger function for employee_jobs table. */
CREATE OR REPLACE FUNCTION employee_jobs_history_trigger()
RETURNS TRIGGER AS $$
DECLARE
  v_trig_enabled VARCHAR(1);
BEGIN
  SELECT COALESCE(current_setting('session.trigs_enabled'), 'Y')
  INTO v_trig_enabled;

  IF v_trig_enabled = 'Y' THEN
    IF(TG_OP = 'UPDATE') THEN
      INSERT INTO employee_history (
        employee_number,
        title,
        first_name,
        middle_name,
        last_name,
        gender,
        ssn,
        birth_date,
        marital_status_code,
        marital_status_name,
        employee_status_code,
        employee_status_name,
        orig_hire_date,
        rehire_date,
        termination_date,
        termination_reason_code,
        termination_reason_name,
        termination_type_code,
        termination_type_name,
        job_code,
        job_title,
        job_st_date,
        job_end_date,
        pay_amount,
        standard_hours,
        employee_type_code,
        employee_type_name,
        employment_status_code,
        employment_status_name,
        department_code,
        department_name,
        location_code,
        location_name,
        pay_frequency_code,
        pay_frequency_name,
        pay_type_code,
        pay_type_name,
        supervisor_job_code,
        supervisor_job_title,
        history_timestamp
      )
      VALUES (
        (SELECT e.employee_number
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.title
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.first_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.middle_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.last_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.gender
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.ssn
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.birth_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.marital_status_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.marital_status_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.code
          FROM employee_statuses e
          WHERE e.id = NEW.employee_status_id),

        (SELECT e.name
          FROM employee_statuses e
          WHERE e.id = NEW.employee_status_id),

        (SELECT e.orig_hire_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.rehire_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.termination_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.termination_reason_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.termination_reason_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.termination_type_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.termination_type_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT j.code
          FROM jobs j
          WHERE j.id = NEW.job_id),

        (SELECT j.name
          FROM jobs j
          WHERE j.id = NEW.job_id),

        NEW.effective_date,
        NEW.expiry_date,
        NEW.pay_amount,
        NEW.standard_hours,

        (SELECT e.code
          FROM employee_types e
          WHERE e.id = NEW.employee_type_id),

        (SELECT e.name
          FROM employee_types e
          WHERE e.id = NEW.employee_type_id),

        (SELECT e.employment_status_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.employment_status_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.department_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.department_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.location_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.location_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.pay_frequency_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.pay_frequency_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.pay_type_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.pay_type_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.supervisor_job_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        (SELECT e.supervisor_job_title
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = NEW.employee_id),

        CURRENT_TIMESTAMP
      );
      RETURN NEW;
    ELSEIF(TG_OP = 'DELETE') THEN
      INSERT INTO employee_history (
        employee_number,
        title,
        first_name,
        middle_name,
        last_name,
        gender,
        ssn,
        birth_date,
        marital_status_code,
        marital_status_name,
        employee_status_code,
        employee_status_name,
        orig_hire_date,
        rehire_date,
        termination_date,
        termination_reason_code,
        termination_reason_name,
        termination_type_code,
        termination_type_name,
        job_code,
        job_title,
        job_st_date,
        job_end_date,
        pay_amount,
        standard_hours,
        employee_type_code,
        employee_type_name,
        employment_status_code,
        employment_status_name,
        department_code,
        department_name,
        location_code,
        location_name,
        pay_frequency_code,
        pay_frequency_name,
        pay_type_code,
        pay_type_name,
        supervisor_job_code,
        supervisor_job_title,
        history_timestamp
      )
      VALUES (
        (SELECT e.employee_number
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.title
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.first_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.middle_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.last_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.gender
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.ssn
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.birth_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.marital_status_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.marital_status_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.code
          FROM employee_statuses e
          WHERE e.id = OLD.employee_status_id),

        (SELECT e.name
          FROM employee_statuses e
          WHERE e.id = OLD.employee_status_id),

        (SELECT e.orig_hire_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.rehire_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.termination_date
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.termination_reason_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.termination_reason_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.termination_type_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.termination_type_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT j.code
          FROM jobs j
          WHERE j.id = OLD.job_id),

        (SELECT j.name
          FROM jobs j
          WHERE j.id = OLD.job_id),

        OLD.effective_date,
        OLD.expiry_date,
        OLD.pay_amount,
        OLD.standard_hours,

        (SELECT e.code
          FROM employee_types e
          WHERE e.id = OLD.employee_type_id),

        (SELECT e.name
          FROM employee_types e
          WHERE e.id = OLD.employee_type_id),

        (SELECT e.employment_status_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.employment_status_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.department_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.department_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.location_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.location_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.pay_frequency_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.pay_frequency_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.pay_type_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.pay_type_name
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.supervisor_job_code
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        (SELECT e.supervisor_job_title
          FROM employee_history e, employee_jobs ej
          WHERE ej.employee_id = OLD.employee_id),

        CURRENT_TIMESTAMP
      );
      RETURN OLD;
    END IF;
  END IF;
  RETURN NULL;
END;
$$ LANGUAGE plpgsql;


/* Create history update trigger for employee_jobs table. */
CREATE TRIGGER b_employee_jobs_history_update_trigger
AFTER UPDATE ON employee_jobs
FOR EACH ROW WHEN(OLD.* != NEW.*)
EXECUTE PROCEDURE employee_jobs_history_trigger();

/* Create history delete trigger for employee_jobs table. */
CREATE TRIGGER a_employee_jobs_history_delete_trigger
AFTER DELETE ON employee_jobs
FOR EACH ROW
WHEN(OLD.* IS NOT NULL)
EXECUTE PROCEDURE employee_jobs_history_trigger();
