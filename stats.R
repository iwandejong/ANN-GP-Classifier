# Read outputs.csv and generate statistics
library(ggplot2)
library(gghighlight)

# Load the data
data <- read.csv("outputs.csv")

# Generate statistics
mean(data$Output)
mean(data$Actual)
mean(data$Expected)

# Calculate standard deviation
sd(data$Output)
sd(data$Actual)
sd(data$Expected)

# Generate plots
plot(data$Output)
  
# Add a title
ggplot(data, aes(x=Output)) + 
  geom_density(fill="blue", alpha=0.5) +
  geom_vline(aes(xintercept=mean(Output)), color="red", size=1) +
  geom_vline(aes(xintercept=mean(Actual)), color="green", size=1) +
  geom_vline(aes(xintercept=mean(Expected)), color="blue", size=1) +
  theme_minimal()

# Save the plots
png("output_plot.png")