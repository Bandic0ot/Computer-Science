/* Part 2 */
/* Question 1 */
SELECT u.name AS University,
       d.name AS Department,
       c.code AS Course_Code,
       c.name AS Course_Name,
       c.course_desc,
       c.credit_units
FROM universities u,
     departments d,
     courses c
WHERE u.id = 1
  AND u.id = d.university_id
  AND d.id = c.department_id;

/* Question 2 */
SELECT COUNT (s.id) AS Enrollment_Count
FROM sections s
WHERE s.num_enrolled IN (SELECT COUNT (e.section_id)
                                 FROM enrollments e
                             GROUP BY e.section_id);
     
/* Question 3 */ /* Implicit Joins */
SELECT c.code,
       c.name,
       s.lec_type,
       s.max_enrollment,
       s.max_enrollment - s.num_enrolled AS Available_Slots,
       i.last_name,
       t.start_date,
       t.end_date,
       s.start_time,
       s.end_time
FROM courses c,
     sections s,
     instructors i,
     terms t
WHERE s.course_id = c.id
  AND s.term_id = t.id
  AND s.instructor_id = i.id
  AND c.department_id = 1;

/* Explicit Joins */
SELECT c.code,
       c.name,
       s.lec_type,
       s.max_enrollment,
       s.max_enrollment - s.num_enrolled AS Available_Slots,
       i.last_name,
       t.start_date,
       t.end_date,
       s.start_time,
       s.end_time
FROM sections s
JOIN courses c ON s.course_id = c.id
JOIN terms t ON s.term_id = t.id
JOIN instructors i ON s.instructor_id = i.id
WHERE c.department_id = 1;

/* Question 4 */
SELECT c.code, c.name, section_info.lec_type,section_info.num_sections
FROM courses c,
  (SELECT s.course_id, s.lec_type, COUNT(s.section_code) AS num_sections
   FROM sections s
   GROUP BY s.course_id, s.lec_type) AS section_info
WHERE section_info.course_id = c.id
ORDER BY c.code, section_info.num_sections;

/* Question 5 */
SELECT c.code, c.name, s.section_code, s.lec_type,
CASE
  WHEN s.num_enrolled > s.max_enrollment THEN 'Section Over-Filled'
  WHEN s.num_enrolled = s.max_enrollment THEN 'Section Full'
  WHEN s.num_enrolled < s.max_enrollment THEN 'Room Available'
END AS Section_Status
FROM courses c, sections s
WHERE c.id = s.course_id;


/* Part 3 */
/* Question 2 */
CREATE TABLE assessments(
  id INT,
  name VARCHAR(100) NOT NULL,
  type CHAR(1),
  total_points FLOAT,
  weight FLOAT,
  due_date DATE,
  section_id INT NOT NULL REFERENCES sections,
  PRIMARY KEY (id));

CREATE TABLE enrollment_assessments(
  id INT,
  enrollment_id INT NOT NULL REFERENCES enrollments,
  assessments_id INT NOT NULL REFERENCES assessments,
  points FLOAT,
  PRIMARY KEY (id));

/* Question 3 */
INSERT INTO assessments (id, name, type, total_points, weight, due_date, section_id)
VALUES  (1, 'Assignment 1', 'A', 100, 10, TO_DATE('9, 25, 2017', 'MM/DD/YYYY'), 82736),
        (2, 'Assignment 2', 'A', 100, 10, TO_DATE('10, 01, 2017', 'MM/DD/YYYY'), 82736),
        (3, 'Assignment 3', 'A', 100, 10, TO_DATE('10, 15, 2017', 'MM/DD/YYYY'), 82736),
        (4, 'Assignment 4', 'A', 100, 10, TO_DATE('10, 29, 2017', 'MM/DD/YYYY'), 82736),
        (5, 'Assignment 5', 'A', 100, 10, TO_DATE('11, 14, 2017', 'MM/DD/YYYY'), 82736),
        (6, 'Midterm', 'M', 100, 20, TO_DATE('11, 20, 2017', 'MM/DD/YYYY'), 82736),
        (7, 'Final', 'F', 100, 30, TO_DATE('12, 8, 2017', 'MM/DD/YYYY'), 82736);

/* Question 4 */
UPDATE sections
SET instructor_id = NULL
WHERE instructor_id = 1;

DELETE FROM instructors i
WHERE i.id = 1;

INSERT INTO instructors (id, employee_number, first_name, last_name, seniority_date, email_address)
VALUES (1, 42, 'Ellen', 'Redlick', TO_DATE('9, 6, 2017', 'MM/DD/YYYY'), 'dopedatabasedisciplinarian@usask.ca');

UPDATE sections
SET instructor_id = 1
WHERE course_id = 10;
