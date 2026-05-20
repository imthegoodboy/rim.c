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























