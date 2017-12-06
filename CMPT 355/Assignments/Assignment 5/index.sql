/* Matthew Mulenga */
/* mam558 */
/* 11144528 */

CREATE INDEX employee_name_index ON employee_history(first_name, last_name);
CREATE INDEX employee_birth_date_index ON employees(birth_date);
CREATE INDEX employee_jobs_id_index ON employee_jobs(employee_id, job_id);

-- Without Index
--Query 1
--Seq Scan on employee_history eh  (cost=0.00..116.14 rows=1 width=268) (actual time=0.080..1.153 rows=12 loops=1)
  --Filter: ((first_name)::text ~~ 'Cla%'::text)
  --Rows Removed by Filter: 1683
--Planning time: 0.127 ms
--Execution time: 1.189 ms

--Query 2
--Seq Scan on employee_history eh  (cost=0.00..116.14 rows=1691 width=268) (actual time=0.028..1.566 rows=1681 loops=1)
  --Filter: ((first_name)::text !~~ 'Cla%'::text)
  --Rows Removed by Filter: 14
--Planning time: 0.100 ms
--Execution time: 1.799 ms

--Query 3
--Nested Loop  (cost=0.00..110.85 rows=1 width=237) (actual time=0.684..1.981 rows=30 loops=1)
  --Join Filter: (e.employment_status_id = es.id)
  --Rows Removed by Join Filter: 32
  --->  Seq Scan on employees e  (cost=0.00..98.96 rows=21 width=23) (actual time=0.649..1.862 rows=31 loops=1)
        --Filter: ((birth_date > (('now'::cstring)::date - '30 years'::interval)) AND (COALESCE(termination_date, --(('now'::cstring)::date + 1)) >= ('now'::cstring)::date))
        --Rows Removed by Filter: 825
  --->  Materialize  (cost=0.00..11.26 rows=2 width=222) (actual time=0.001..0.002 rows=2 loops=31)
        --->  Seq Scan on employment_status_types es  (cost=0.00..11.25 rows=2 width=222) (actual time=0.025..0.027 rows=2 loops=1)
              --Filter: ((name)::text = ANY ('{Active,"Paid Leave"}'::text[]))
              --Rows Removed by Filter: 3
--Planning time: 0.319 ms
--Execution time: 2.037 ms

--Query 4
--->  Nested Loop  (cost=0.28..170.54 rows=17 width=235) (actual time=0.053..6.190 rows=367 loops=1)
      --Join Filter: (e.employment_status_id = es.id)
      --Rows Removed by Join Filter: 1345
      --->  Index Scan using employees_pkey on employees e  (cost=0.28..133.61 rows=856 width=21) (actual time=0.006..0.636 rows=856 loops=1)
      --->  Materialize  (cost=0.00..11.26 rows=2 width=222) (actual time=0.000..0.000 rows=2 loops=856)
            --->  Seq Scan on employment_status_types es  (cost=0.00..11.25 rows=2 width=222) (actual time=0.024..0.027 rows=2 loops=1)
                  --Filter: ((name)::text = ANY ('{Active,"Paid Leave"}'::text[]))
                  --Rows Removed by Filter: 3
--->  Sort  (cost=66.94..66.97 rows=12 width=265) (actual time=0.989..1.041 rows=186 loops=1)
      --Sort Key: ej.employee_id
      --Sort Method: quicksort  Memory: 48kB
      --->  Hash Join  (cost=18.82..66.72 rows=12 width=265) (actual time=0.376..0.892 rows=186 loops=1)
            --Hash Cond: (ej.job_id = j.id)
            --->  Seq Scan on employee_jobs ej  (cost=0.00..44.56 rows=856 width=20) (actual time=0.054..0.401 rows=856 loops=1)
            --->  Hash  (cost=18.80..18.80 rows=2 width=253) (actual time=0.209..0.209 rows=26 loops=1)
                  --Buckets: 1024  Batches: 1  Memory Usage: 11kB
                  --->  Hash Join  (cost=9.91..18.80 rows=2 width=253) (actual time=0.143..0.198 rows=26 loops=1)
                        --Hash Cond: (j.department_id = d.id)
                        --->  Seq Scan on jobs j  (cost=0.00..8.35 rows=135 width=25) (actual time=0.010..0.061 rows=135 loops=1)
                        --->  Hash  (cost=9.90..9.90 rows=1 width=236) (actual time=0.080..0.080 rows=10 loops=1)
                              --Buckets: 1024  Batches: 1  Memory Usage: 9kB
                              --->  Hash Join  (cost=8.17..9.90 rows=1 width=236) (actual time=0.054..0.075 rows=10 loops=1)
                                    --Hash Cond: (d.location_id = l.id)
                                    --->  Seq Scan on departments d  (cost=0.00..1.52 rows=52 width=22) (actual time=0.003..0.011 rows=52 loops=1)
                                    --->  Hash  (cost=8.16..8.16 rows=1 width=222) (actual time=0.033..0.033 rows=1 loops=1)
                                          --Buckets: 1024  Batches: 1  Memory Usage: 9kB
                                          --->  Index Scan using locations_code_key on locations l  (cost=0.14..8.16 rows=1 width=222) (actual time=0.026..0.026 rows=1 loops=1)
                                                --Index Cond: ((code)::text = 'SKTN-MT'::text)
--SubPlan 1
  --->  Aggregate  (cost=46.70..46.71 rows=1 width=4) (actual time=0.185..0.185 rows=1 loops=77)
        --->  Seq Scan on employee_jobs ej2  (cost=0.00..46.70 rows=1 width=4) (actual time=0.113..0.183 rows=1 loops=77)
              --Filter: (employee_id = e.id)
              --Rows Removed by Filter: 855
--Planning time: 1.180 ms
--Execution time: 23.184 ms


-- With Index
--Query 1
--Seq Scan on employee_history eh  (cost=0.00..116.19 rows=1 width=268) (actual time=0.116..2.575 rows=12 loops=1)
  --Filter: ((first_name)::text ~~ 'Cla%'::text)
  --Rows Removed by Filter: 1683
--Planning time: 0.552 ms
--Execution time: 2.653 ms

--Query 2
--Seq Scan on employee_history eh  (cost=0.00..116.19 rows=1695 width=268) (actual time=0.044..2.788 rows=1681 loops=1)
  --Filter: ((first_name)::text !~~ 'Cla%'::text)
  --Rows Removed by Filter: 14
--Planning time: 0.314 ms
--Execution time: 3.365 ms

--Query 3
--Nested Loop  (cost=4.75..88.97 rows=1 width=237) (actual time=0.136..0.445 rows=30 loops=1)
  --Join Filter: (e.employment_status_id = es.id)
  --Rows Removed by Join Filter: 32
  --->  Bitmap Heap Scan on employees e  (cost=4.75..77.09 rows=21 width=23) (actual time=0.103..0.355 rows=31 loops=1)
        --Recheck Cond: (birth_date > (('now'::cstring)::date - '30 years'::interval))
        --Filter: (COALESCE(termination_date, (('now'::cstring)::date + 1)) >= ('now'::cstring)::date)
        --Rows Removed by Filter: 32
        --Heap Blocks: exact=26
        --->  Bitmap Index Scan on employee_birth_date_index  (cost=0.00..4.75 rows=62 width=0) (actual time=0.076..0.076 rows=63 loops=1)
              --Index Cond: (birth_date > (('now'::cstring)::date - '30 years'::interval))
  --->  Materialize  (cost=0.00..11.26 rows=2 width=222) (actual time=0.001..0.001 rows=2 loops=31)
        --->  Seq Scan on employment_status_types es  (cost=0.00..11.25 rows=2 width=222) (actual time=0.025..0.027 rows=2 loops=1)
              --Filter: ((name)::text = ANY ('{Active,"Paid Leave"}'::text[]))
              --Rows Removed by Filter: 3
--Planning time: 0.554 ms
--Execution time: 0.514 ms

--Query 4
--Nested Loop  (cost=10.60..142.78 rows=1 width=492) (actual time=3.482..6.384 rows=77 loops=1)
  --->  Nested Loop  (cost=10.46..142.55 rows=1 width=278) (actual time=3.381..5.915 rows=186 loops=1)
        --->  Nested Loop  (cost=10.18..34.86 rows=12 width=265) (actual time=3.343..4.227 rows=186 loops=1)
              --->  Hash Join  (cost=9.91..18.80 rows=2 width=253) (actual time=3.316..3.417 rows=26 loops=1)
                    --Hash Cond: (j.department_id = d.id)
                    --->  Seq Scan on jobs j  (cost=0.00..8.35 rows=135 width=25) (actual time=2.509..3.221 rows=135 loops=1)
                    --->  Hash  (cost=9.90..9.90 rows=1 width=236) (actual time=0.080..0.080 rows=10 loops=1)
                          --Buckets: 1024  Batches: 1  Memory Usage: 9kB
                          --->  Hash Join  (cost=8.17..9.90 rows=1 width=236) (actual time=0.055..0.074 rows=10 loops=1)
                                --Hash Cond: (d.location_id = l.id)
                                --->  Seq Scan on departments d  (cost=0.00..1.52 rows=52 width=22) (actual time=0.007..0.016 rows=52 loops=1)
                                --->  Hash  (cost=8.16..8.16 rows=1 width=222) (actual time=0.033..0.033 rows=1 loops=1)
                                      --Buckets: 1024  Batches: 1  Memory Usage: 9kB
                                      --->  Index Scan using locations_code_key on locations l  (cost=0.14..8.16 rows=1 width=222) (actual time=0.029..0.030 rows=1 loops=1)
                                            --Index Cond: ((code)::text = 'SKTN-MT'::text)
              --->  Index Scan using employee_jobs_id_index on employee_jobs ej  (cost=0.28..7.97 rows=6 width=20) (actual time=0.012..0.028 rows=7 loops=26)
                    --Index Cond: (job_id = j.id)
        --->  Index Scan using employees_pkey on employees e  (cost=0.28..8.96 rows=1 width=21) (actual time=0.008..0.008 rows=1 loops=186)
              --Index Cond: (id = ej.employee_id)
              ---Filter: (ej.effective_date = (SubPlan 1))
              --SubPlan 1
                --->  Aggregate  (cost=8.29..8.30 rows=1 width=4) (actual time=0.003..0.003 rows=1 loops=186)
                      --->  Index Scan using employee_jobs_id_index on employee_jobs ej2  (cost=0.28..8.29 rows=1 width=4) (actual time=0.002..0.002 rows=1 loops=186)
                            --Index Cond: (employee_id = e.id)
  --->  Index Scan using employment_status_types_pkey on employment_status_types es  (cost=0.14..0.22 rows=1 width=222) (actual time=0.002..0.002 rows=0 loops=186)
        --Index Cond: (id = e.employment_status_id)
        --Filter: ((name)::text = ANY ('{Active,"Paid Leave"}'::text[]))
        --Rows Removed by Filter: 1
--Planning time: 1.133 ms
--Execution time: 6.502 ms
