/* Part 2 */
/* Question 1 */
SELECT u.name,
       d.name,
       c.code,
       c.name,
       c.course_desc,
       c.credit_units
FROM universities u,
     departments d,
     courses c
WHERE u.id = 1
  AND u.id = d.university_id
  AND d.id = c.department_id;

/* Question 2 */
SELECT COUNT (*) AS Course_Match_Count
FROM courses c
WHERE c.id IN
    (SELECT s.course_id
     FROM sections s
     WHERE s.num_enrolled = s.max_enrollment);

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
SELECT c.code,
       c.name,
       section_info.lec_type,
       section_info.num_sections
FROM courses c,

  (SELECT s.course_id,
          s.lec_type,
          COUNT(s.section_code) AS num_sections
   FROM sections s
   GROUP BY s.course_id,
            s.lec_type) AS section_info
WHERE section_info.course_id = c.id
ORDER BY c.code,
         section_info.num_sections;

/* Question 5 */
SELECT c.code,
       c.name,
       s.section_code,
       s.lec_type,
       CASE
           WHEN s.num_enrolled > s.max_enrollment THEN 'Section Over-Filled'
           WHEN s.num_enrolled = s.max_enrollment THEN 'Section Full'
           WHEN s.num_enrolled < s.max_enrollment THEN 'Room Available'
       END AS Section_Status
FROM courses c,
     sections s
WHERE c.id = s.course_id;


/* Part 3 */
/* Question 1 */