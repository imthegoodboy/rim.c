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

















