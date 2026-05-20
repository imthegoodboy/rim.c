 ```sql
-- 1. Create User and Grant Permissions

CREATE USER 'raj2'@'localhost' IDENTIFIED BY 'raj2';

GRANT ALL PRIVILEGES ON raj.* TO 'raj2'@'localhost';

FLUSH PRIVILEGES;

-- ---------------------------------------------------

-- Create Database

CREATE DATABASE raj;

SHOW DATABASES;

USE raj;

-- ---------------------------------------------------

-- 2. Create Employee Table

CREATE TABLE Employee (
    EMPNO INT,
    ENAME VARCHAR(20),
    JOB VARCHAR(20),
    MANAGER_NO INT,
    SAL DECIMAL(10,2),
    COMMISSION DECIMAL(10,2)
);

-- Display Table Structure

DESC Employee;

-- ---------------------------------------------------

-- Insert Three Records

INSERT INTO Employee 
VALUES (101, 'Ravi', 'Manager', 201, 50000, 5000);

INSERT INTO Employee 
VALUES (102, 'Anita', 'Clerk', 101, 20000, 1000);

INSERT INTO Employee 
VALUES (103, 'Suresh', 'Salesman', 101, 25000, 2000);

-- Display Records

SELECT * FROM Employee;

-- ---------------------------------------------------

-- Use Rollback

SET AUTOCOMMIT = 0;

INSERT INTO Employee
VALUES (104, 'Mahesh', 'Watchman', 104, 243400, 2400);

-- Check Record Before Rollback

SELECT * FROM Employee;

-- Rollback Transaction

ROLLBACK;

-- Verify Result After Rollback

SELECT * FROM Employee;

-- ---------------------------------------------------

-- 3. Add Primary Key Constraint

ALTER TABLE Employee
ADD CONSTRAINT emp_pk PRIMARY KEY (EMPNO);

-- Add NOT NULL Constraint to ENAME

ALTER TABLE Employee
MODIFY ENAME VARCHAR(10) NOT NULL;

-- Verify Table Structure

DESC Employee;

-- ---------------------------------------------------

-- 4. Insert NULL Values and Verify Result

INSERT INTO Employee
VALUES (104, NULL, 'Watchman', 104, 243400, 2400);

-- Expected Output:
-- ERROR 1048 (23000): Column 'ENAME' cannot be null
```






```sql id="4gkq2n"
-- Experiment: Employee Table Creation and Operations

-- 1. Create Employee Table

CREATE TABLE Employee (
    EMPNO INT PRIMARY KEY,
    ENAME VARCHAR(50) NOT NULL,
    JOB VARCHAR(30),
    MGR INT,
    SAL DECIMAL(10,2)
);

-- Output:
-- Query OK, 0 rows affected

-- ---------------------------------------------------

-- 2. Add COMMISSION Column with Domain Constraint

ALTER TABLE Employee
ADD COMMISSION DECIMAL(10,2)
CHECK (COMMISSION >= 0);

-- Output:
-- Query OK, 0 rows affected

-- ---------------------------------------------------

-- 3. Insert Five Records

INSERT INTO Employee 
(EMPNO, ENAME, JOB, MGR, SAL, COMMISSION)
VALUES
(101, 'Ramesh', 'Manager', NULL, 75000, 5000),
(102, 'Suresh', 'Clerk', 101, 25000, 1000),
(103, 'Mahesh', 'Analyst', 101, 45000, 3000),
(104, 'Anita', 'HR', 101, 40000, 2000),
(105, 'Kiran', 'Salesman', 101, 30000, 1500);

-- Output:
-- Query OK, 5 rows affected

-- Display Table Records

SELECT * FROM Employee;

-- Expected Output:
-- +--------+---------+----------+------+----------+------------+
-- | EMPNO  | ENAME   | JOB      | MGR  | SAL      | COMMISSION |
-- +--------+---------+----------+------+----------+------------+
-- | 101    | Ramesh  | Manager  | NULL | 75000.00 | 5000.00    |
-- | 102    | Suresh  | Clerk    | 101  | 25000.00 | 1000.00    |
-- | 103    | Mahesh  | Analyst  | 101  | 45000.00 | 3000.00    |
-- | 104    | Anita   | HR       | 101  | 40000.00 | 2000.00    |
-- | 105    | Kiran   | Salesman | 101  | 30000.00 | 1500.00    |
-- +--------+---------+----------+------+----------+------------+

-- ---------------------------------------------------

-- 4. Update JOB Column Details

UPDATE Employee
SET JOB = 'Senior Clerk'
WHERE EMPNO = 102;

-- Output:
-- Query OK, 1 row affected

-- Verify Updated Record

SELECT EMPNO, ENAME, JOB
FROM Employee
WHERE EMPNO = 102;

-- Expected Output:
-- +--------+---------+---------------+
-- | EMPNO  | ENAME   | JOB           |
-- +--------+---------+---------------+
-- | 102    | Suresh  | Senior Clerk  |
-- +--------+---------+---------------+

-- ---------------------------------------------------

-- 5. Rename Column JOB to DESIGNATION

ALTER TABLE Employee
CHANGE JOB DESIGNATION VARCHAR(30);

-- Output:
-- Query OK, 0 rows affected

-- Verify Table Structure

DESC Employee;

-- ---------------------------------------------------

-- 6. Delete Employee with EMPNO = 105

DELETE FROM Employee
WHERE EMPNO = 105;

-- Output:
-- Query OK, 1 row affected

-- Display Remaining Records

SELECT * FROM Employee;

-- Expected Output:
-- +--------+---------+---------------+------+----------+------------+
-- | EMPNO  | ENAME   | DESIGNATION   | MGR  | SAL      | COMMISSION |
-- +--------+---------+---------------+------+----------+------------+
-- | 101    | Ramesh  | Manager       | NULL | 75000.00 | 5000.00    |
-- | 102    | Suresh  | Senior Clerk  | 101  | 25000.00 | 1000.00    |
-- | 103    | Mahesh  | Analyst       | 101  | 45000.00 | 3000.00    |
-- | 104    | Anita   | HR            | 101  | 40000.00 | 2000.00    |
-- +--------+---------+---------------+------+----------+------------+
```









```sql id="v7m2xp"
-- Program - 3
-- Queries using Aggregate Functions, GROUP BY, ORDER BY

-- ---------------------------------------------------
-- Create Database

CREATE DATABASE program03;

USE program03;

-- ---------------------------------------------------
-- 1. Create Employee Table

CREATE TABLE Employee (
    E_id INT PRIMARY KEY,
    E_name VARCHAR(50),
    Age INT,
    Salary DECIMAL(10,2)
);

-- Insert Records into Employee Table

INSERT INTO Employee VALUES
(101, 'Ravi', 25, 30000),
(102, 'Anita', 30, 45000),
(103, 'Kiran', 28, 35000),
(104, 'Suresh', 35, 50000),
(105, 'Meena', 27, 40000);

-- Display Records

SELECT * FROM Employee;

-- Expected Output:
-- +------+---------+-----+----------+
-- | E_id | E_name  | Age | Salary   |
-- +------+---------+-----+----------+
-- | 101  | Ravi    | 25  | 30000.00 |
-- | 102  | Anita   | 30  | 45000.00 |
-- | 103  | Kiran   | 28  | 35000.00 |
-- | 104  | Suresh  | 35  | 50000.00 |
-- | 105  | Meena   | 27  | 40000.00 |
-- +------+---------+-----+----------+

-- ---------------------------------------------------
-- 2. Count Number of Employee Names

SELECT COUNT(E_name) AS Total_Employees
FROM Employee;

-- Expected Output:
-- +-----------------+
-- | Total_Employees |
-- +-----------------+
-- | 5               |
-- +-----------------+

-- ---------------------------------------------------
-- 3. Find Maximum Age

SELECT MAX(Age) AS Maximum_Age
FROM Employee;

-- Expected Output:
-- +-------------+
-- | Maximum_Age |
-- +-------------+
-- | 35          |
-- +-------------+

-- ---------------------------------------------------
-- 4. Find Minimum Age

SELECT MIN(Age) AS Minimum_Age
FROM Employee;

-- Expected Output:
-- +-------------+
-- | Minimum_Age |
-- +-------------+
-- | 25          |
-- +-------------+

-- ---------------------------------------------------
-- 5. Find Salaries in Ascending Order

SELECT E_name, Salary
FROM Employee
ORDER BY Salary ASC;

-- Expected Output:
-- +---------+----------+
-- | E_name  | Salary   |
-- +---------+----------+
-- | Ravi    | 30000.00 |
-- | Kiran   | 35000.00 |
-- | Meena   | 40000.00 |
-- | Anita   | 45000.00 |
-- | Suresh  | 50000.00 |
-- +---------+----------+

-- ---------------------------------------------------
-- 6. Find Grouped Salaries of Employees

SELECT Salary,
COUNT(*) AS Number_of_Employees
FROM Employee
GROUP BY Salary;

-- Expected Output:
-- +----------+---------------------+
-- | Salary   | Number_of_Employees |
-- +----------+---------------------+
-- | 30000.00 | 1                   |
-- | 35000.00 | 1                   |
-- | 40000.00 | 1                   |
-- | 45000.00 | 1                   |
-- | 50000.00 | 1                   |
-- +----------+---------------------+

-- ---------------------------------------------------
-- Insert One More Employee with Same Salary

INSERT INTO Employee
VALUES (106, 'Vikram', 26, 30000);

-- Display Grouped Salaries Again

SELECT Salary,
COUNT(*) AS Number_of_Employees
FROM Employee
GROUP BY Salary;

-- Expected Output:
-- +----------+---------------------+
-- | Salary   | Number_of_Employees |
-- +----------+---------------------+
-- | 30000.00 | 2                   |
-- | 35000.00 | 1                   |
-- | 40000.00 | 1                   |
-- | 45000.00 | 1                   |
-- | 50000.00 | 1                   |
-- +----------+---------------------+
```





```sql id="x8qk31"
-- Program - 4
-- Row Level Trigger on CUSTOMERS Table

-- ---------------------------------------------------
-- 1. Create CUSTOMERS Table

CREATE TABLE CUSTOMERS (
    ID INT PRIMARY KEY,
    NAME VARCHAR(50),
    AGE INT,
    ADDRESS VARCHAR(100),
    SALARY DECIMAL(10,2)
);

-- ---------------------------------------------------
-- 2. Insert Values into CUSTOMERS Table

INSERT INTO CUSTOMERS
VALUES (10, 'Abhi', 25, 'Bangalore', 10000);

INSERT INTO CUSTOMERS
VALUES (20, 'Mukund', 35, 'Mangalore', 20000);

INSERT INTO CUSTOMERS
VALUES (30, 'Shiva', 34, 'Jaipur', 30000);

-- Display Records

SELECT * FROM CUSTOMERS;

-- Expected Output:
-- +----+--------+------+-----------+----------+
-- | ID | NAME   | AGE  | ADDRESS   | SALARY   |
-- +----+--------+------+-----------+----------+
-- | 10 | Abhi   | 25   | Bangalore | 10000.00 |
-- | 20 | Mukund | 35   | Mangalore | 20000.00 |
-- | 30 | Shiva  | 34   | Jaipur    | 30000.00 |
-- +----+--------+------+-----------+----------+

-- ---------------------------------------------------
-- 3. Create Log Table

CREATE TABLE customer_salary_log (
    id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT,
    action_type VARCHAR(10),
    old_salary DECIMAL(10,2),
    new_salary DECIMAL(10,2),
    difference DECIMAL(10,2),
    log_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ---------------------------------------------------
-- 4. INSERT Trigger

DELIMITER //

CREATE TRIGGER trg_customers_insert
AFTER INSERT ON CUSTOMERS
FOR EACH ROW
BEGIN
    INSERT INTO customer_salary_log
    (customer_id, action_type, old_salary, new_salary, difference)
    VALUES
    (NEW.ID, 'INSERT', NULL, NEW.SALARY, NEW.SALARY);
END //

DELIMITER ;

-- ---------------------------------------------------
-- 5. UPDATE Trigger

DELIMITER //

CREATE TRIGGER trg_customers_update
AFTER UPDATE ON CUSTOMERS
FOR EACH ROW
BEGIN
    INSERT INTO customer_salary_log
    (customer_id, action_type, old_salary, new_salary, difference)
    VALUES
    (NEW.ID, 'UPDATE', OLD.SALARY, NEW.SALARY,
     NEW.SALARY - OLD.SALARY);
END //

DELIMITER ;

-- ---------------------------------------------------
-- 6. DELETE Trigger

DELIMITER //

CREATE TRIGGER trg_customers_delete
AFTER DELETE ON CUSTOMERS
FOR EACH ROW
BEGIN
    INSERT INTO customer_salary_log
    (customer_id, action_type, old_salary, new_salary, difference)
    VALUES
    (OLD.ID, 'DELETE', OLD.SALARY, NULL,
     -OLD.SALARY);
END //

DELIMITER ;

-- ---------------------------------------------------
-- 7. Test INSERT Trigger

INSERT INTO CUSTOMERS
VALUES (40, 'Dhruv', 45, 'Bombay', 50000);

-- View Log Table

SELECT * FROM customer_salary_log;

-- Expected Output:
-- +----+-------------+-------------+------------+------------+------------+---------------------+
-- | id | customer_id | action_type | old_salary | new_salary | difference | log_time            |
-- +----+-------------+-------------+------------+------------+------------+---------------------+
-- | 1  | 40          | INSERT      | NULL       | 50000.00   | 50000.00   | 2026-03-26 11:19:22 |
-- +----+-------------+-------------+------------+------------+------------+---------------------+

-- ---------------------------------------------------
-- 8. Test UPDATE Trigger

UPDATE CUSTOMERS
SET SALARY = 35000
WHERE ID = 10;

-- Display CUSTOMERS Table

SELECT * FROM CUSTOMERS;

-- Display Log Table

SELECT * FROM customer_salary_log;

-- Expected Output:
-- +----+-------------+-------------+------------+------------+------------+---------------------+
-- | id | customer_id | action_type | old_salary | new_salary | difference | log_time            |
-- +----+-------------+-------------+------------+------------+------------+---------------------+
-- | 1  | 40          | INSERT      | NULL       | 50000.00   | 50000.00   | 2026-03-26 11:19:22 |
-- | 2  | 10          | UPDATE      | 10000.00   | 35000.00   | 25000.00   | 2026-03-26 11:22:44 |
-- +----+-------------+-------------+------------+------------+------------+---------------------+

-- ---------------------------------------------------
-- 9. Test DELETE Trigger

DELETE FROM CUSTOMERS
WHERE ID = 40;

-- Display CUSTOMERS Table

SELECT * FROM CUSTOMERS;

-- ---------------------------------------------------
-- 10. View Final Log Table

SELECT * FROM customer_salary_log;

-- Expected Output:
-- +----+-------------+-------------+------------+------------+------------+---------------------+
-- | id | customer_id | action_type | old_salary | new_salary | difference | log_time            |
-- +----+-------------+-------------+------------+------------+------------+---------------------+
-- | 1  | 40          | INSERT      | NULL       | 50000.00   | 50000.00   | 2026-03-26 11:19:22 |
-- | 2  | 10          | UPDATE      | 10000.00   | 35000.00   | 25000.00   | 2026-03-26 11:22:44 |
-- | 3  | 40          | DELETE      | 50000.00   | NULL       | -50000.00  | 2026-03-26 11:24:26 |
-- +----+-------------+-------------+------------+------------+------------+---------------------+
```












 ```sql id="k3m9zs"
-- Program - 5
-- Cursor for Employee Table

-- ---------------------------------------------------
-- Cursor Use Case:
-- Give 10% raise to employees with salary > 5000
-- Give 20% raise to employees with salary <= 5000

-- ---------------------------------------------------
-- 1. Create Employee Table

CREATE TABLE employee (
    eid INT,
    ename VARCHAR(15),
    age INT,
    sal INT
);

-- Output:
-- Query OK, 0 rows affected

-- ---------------------------------------------------
-- 2. Insert Records into Employee Table

INSERT INTO employee VALUES
(10, 'abhi', 35, 10000),
(20, 'rohith', 30, 9000),
(30, 'david', 28, 9000),
(40, 'rahul', 25, 4000),
(50, 'pramod', 23, 5000),
(60, 'suraj', 19, 3500);

-- Output:
-- Query OK, 6 rows affected

-- ---------------------------------------------------
-- 3. Display Employee Table

SELECT * FROM employee;

-- Expected Output:
-- +------+--------+------+-------+
-- | eid  | ename  | age  | sal   |
-- +------+--------+------+-------+
-- | 10   | abhi   | 35   | 10000 |
-- | 20   | rohith | 30   | 9000  |
-- | 30   | david  | 28   | 9000  |
-- | 40   | rahul  | 25   | 4000  |
-- | 50   | pramod | 23   | 5000  |
-- | 60   | suraj  | 19   | 3500  |
-- +------+--------+------+-------+

-- ---------------------------------------------------
-- 4. Check Existing Procedures

SHOW PROCEDURE STATUS
WHERE db = 'your_database_name';

-- Example:
-- WHERE db = 'program05';

-- ---------------------------------------------------
-- 5. Drop Existing Procedure (If Exists)

DROP PROCEDURE IF EXISTS cursor_demo_sal_increment;

-- ---------------------------------------------------
-- 6. Create Cursor Procedure

DELIMITER $$

CREATE PROCEDURE cursor_demo_sal_increment()

BEGIN

    DECLARE v_eid INT;
    DECLARE v_sal INT;

    DECLARE completed INT DEFAULT 0;

    -- Declare Cursor
    DECLARE c1 CURSOR FOR
    SELECT eid, sal FROM employee;

    -- Handler for End of Cursor
    DECLARE CONTINUE HANDLER
    FOR NOT FOUND
    SET completed = 1;

    -- Open Cursor
    OPEN c1;

    read_loop: LOOP

        -- Fetch Values
        FETCH c1 INTO v_eid, v_sal;

        -- Exit Condition
        IF completed THEN
            LEAVE read_loop;
        END IF;

        -- Salary Increment Logic
        IF v_sal > 5000 THEN

            UPDATE employee
            SET sal = v_sal * 1.10
            WHERE eid = v_eid;

            SELECT CONCAT(v_eid, ' ', v_sal,
            ' increased by 10%')
            AS 'emp id emp sal';

        ELSE

            UPDATE employee
            SET sal = v_sal * 1.20
            WHERE eid = v_eid;

            SELECT CONCAT(v_eid, ' ', v_sal,
            ' increased by 20%')
            AS 'emp id emp sal';

        END IF;

    END LOOP;

    -- Close Cursor
    CLOSE c1;

END$$

DELIMITER ;

-- ---------------------------------------------------
-- 7. Call Cursor Procedure

CALL cursor_demo_sal_increment();

-- Expected Output:
-- +---------------------------+
-- | emp id emp sal            |
-- +---------------------------+
-- | 10 10000 increased by 10% |
-- +---------------------------+

-- +--------------------------+
-- | emp id emp sal           |
-- +--------------------------+
-- | 20 9000 increased by 10% |
-- +--------------------------+

-- +--------------------------+
-- | emp id emp sal           |
-- +--------------------------+
-- | 30 9000 increased by 10% |
-- +--------------------------+

-- +--------------------------+
-- | emp id emp sal           |
-- +--------------------------+
-- | 40 4000 increased by 20% |
-- +--------------------------+

-- +--------------------------+
-- | emp id emp sal           |
-- +--------------------------+
-- | 50 5000 increased by 20% |
-- +--------------------------+

-- +--------------------------+
-- | emp id emp sal           |
-- +--------------------------+
-- | 60 3500 increased by 20% |
-- +--------------------------+

-- ---------------------------------------------------
-- 8. Check Updated Employee Table

SELECT * FROM employee;

-- Expected Output:
-- +------+--------+------+-------+
-- | eid  | ename  | age  | sal   |
-- +------+--------+------+-------+
-- | 10   | abhi   | 35   | 11000 |
-- | 20   | rohith | 30   | 9900  |
-- | 30   | david  | 28   | 9900  |
-- | 40   | rahul  | 25   | 4800  |
-- | 50   | pramod | 23   | 6000  |
-- | 60   | suraj  | 19   | 4200  |
-- +------+--------+------+-------+

 ```






 







