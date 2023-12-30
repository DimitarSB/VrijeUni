setwd("C:/Users/dbach/OneDrive/Desktop/C++VU/Statistics/R statistics")

#4.3.a
data <- read.table(file = "crimemale.txt", header = TRUE, stringsAsFactors = FALSE)
data.matrix <- as.matrix(data)
data.matrix

#Extracting the singular data from the matrix
data.age <- data.matrix[, 1:1]
data.age

data.income <- data.matrix[, 2:2]
data.income

data.crimes <- data.matrix[, 3:3]
data.crimes

#Scatter plot
plot(data.age, data.crimes, xlab = "Age", ylab = "Crimes", pch = 11, col = "purple" , main = "Scatter plot of the crimes at diffirent age")

#Sample linear correlation coefficient
corResultsAgeCrimes = cor(data.age, data.crimes)
corResultsAgeCrimes

# From the plot we can see a lot of spreading of the dots which could lead us to believe that there is no linear
# correlation between the 2 variables, which is furthermore supported by the cor. coefficient of ~ -0.07 which is
# closer the 0 then to 1/-1

# 4.3.b
#Scatter plot
plot(data.income, data.crimes, xlab = "Income", ylab = "Crimes", pch = 18, col = "orange" , main = "Scatter plot of the crimes at diffirent incomes")

#Sample linear correlation coefficient
corResultsIncomeCrimes = cor(data.income, data.crimes)
corResultsIncomeCrimes


# From the scatter plot and from the cor. coefficient (~0.8 almost a 1) we can deduce that we have a positive
# linear correlation between the 2 variables

# 4.3.c
cor.test(data.crimes, data.income)
lmResults = lm(data.crimes~data.income)
summary(lmResults)
lmResults$coef
lmResults$res
summary(lmResults)$coef[,2]
abline(lmResults$coef)
# slope = 0.286
# Intercept = 1.781

# 4.3.d

# H0: There is a linear relationship between crimes and income
# H1: There is not a linear relationship between crimes and income
# Significance level 1% = 0.01
# Data yields b1 = 0.286 / Sb1 = 0.055
# Test statistic has t-distribution with df = 16 => tB = b1/Sb1 ~5.2
b1 = 0.286
Sb1 = 0.055
tB = b1 / Sb1 # The value is close to the one we found from the test above
tB

# Critical value
qt(p = 0.01/2, df = 16, lower.tail = FALSE) #Critical value ~ -2.92 and +2.92

# Since the 5.2 > 2.9 we reject H0
# There is sufficient evidence to warrant rejection of the claim that there is no
# linear relationship between crimes and income.

# 4.3.e

lmResults
summary(lmResults)
residuals = rstandard(lmResults)
residuals
qqnorm(residuals, main = "QQ plot of residuals", pch = 20 )
qqline(residuals, col = "red")

#Scatter plot
plot(data.income, residuals, xlab = "Income", ylab = "Residuals", pch = 8, main = "Scatter plot of income against risiduals")
# There is no obvious pattern in the dots, and no increase/decrease of residuals with x variables.




