library(ggplot2)


xe <- 1:100
first <- 1 : 1000
second <- first * first

ye <- cumsum(xe)
ddf <- data.frame(first, second)
df <- data.frame(xe, ye)

ggplot() +
  #geom_line(data = ddf, mapping = aes(x = first + 1, y = second), color = "orange") +
  #geom_line(data = df, mapping = aes(x = ye, y = ye), color = "purple") +
  geom_line(data = ddf, mapping = aes(x = first, y = second), color = "purple") +
  #geom_point(data = ddf, mapping = aes(x = first, y = second), color = "black") +
  geom_area(data = ddf, mapping = aes(x = first, y = second), color = "green") +
  geom_bar(data = ddf, mapping = aes(x = first), color = "orange") +
  geom_line(data = ddf, mapping = aes(x = -first, y = -second), color = "purple") +
  geom_area(data = ddf, mapping = aes(x = first, y = second), color = "green") +
  geom_bar(data = ddf, mapping = aes(x = first), color = "yellow")