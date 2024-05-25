# Read outputs.csv and generate statistics
library(ggplot2)
library(gghighlight)

# Load the data
data <- read.csv("GP_outputs.csv")

# Generate statistics
mean(data$Output)
mean(data$Actual)
mean(data$Expected)

# Calculate standard deviation
sd(data$Output)
sd(data$Actual)
sd(data$Expected)

# Generate plots
# show more details in x axis
plot(data$Output, xlim=c(0, 600), ylim=c(0, 1), xlab="Mushroom", ylab="Output")
# if actual = true, then output should be green, otherwise red
points(data$Output, col=ifelse(data$Actual == data$Expected, "green", "red"))
# draw a line on 0.5
abline(h=0.8, col="blue")



  
# Add a title
ggplot(data, aes(x=Output)) + 
  geom_density(fill="blue", alpha=0.5) +
  geom_vline(aes(xintercept=mean(Output)), color="red", size=1) +
  geom_vline(aes(xintercept=mean(Actual)), color="green", size=1) +
  geom_vline(aes(xintercept=mean(Expected)), color="blue", size=1) +
  theme_minimal()

# Load error from epoch
error <- read.csv("GP_error.csv")

# Generate error plot
ggplot(error, aes(x=Generation, y=TrainingAcc)) +
  geom_line() +
  theme_minimal()