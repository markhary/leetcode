SELECT employee.Name AS Employee
FROM Employee employee JOIN Employee manager
ON employee.ManagerId = manager.Id
AND employee.Salary > manager.Salary;
