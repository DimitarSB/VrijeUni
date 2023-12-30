  
  setwd("C:/Users/dbach/OneDrive/Desktop/C++VU/R statistics")
  x2 = seq(5,13, by = 0.3)
  x2
  m = matrix(x2, nrow = 9, ncol = 3)
  value = m[5, 2]
  m[ ,2]
  v = mean(m)
  v
  apply(m, 2, mean)
  
  source("C:/Users/dbach/OneDrive/Desktop/C++VU/R statistics/lepton.txt")
  
  lepton[[1]][2]
  lepton[[1]]
  
  v = scan(file = "sample1.txt")
  me = matrix(v, nrow = 4, ncol = 5)
  dimnames(me) = list(letters[1 : 4], c(as.roman(1 : 5)))
  me
  
  
  
  
  
  
  par(mfrow=c(1,3))
  hist(me , main="A Histogram of sample frequency per unit",
       xlab= "sample data",
       ylab="Frequency",
       ylim = c(0,10))
  
  quadfunc = function(mat){
    mat^4
  }
  
  line = function(mat){
    5*mat+2
  }
  
  roww = seq(0, 2)
  roww
  coll = quadfunc(x)
  coll
  plot(roww, coll, xlab="x", ylab="y", main ="Plot of quadtic and line funcitions", type="l", col = "orange")
  lines(roww, col = "purple", line(roww))
  
  is.numeric(school)
  table(school)
  barplot(table(school), ylim = c(0, 12), col=c("blue","green","black","yellow"), main = "School histogram")
  
  par(mfrow=c(1,1))
  slices <- c(0.37, 0.17, 0.28, 0.07, 0.06, 0.05)
  lbls <- c("Cheesecake", "Pear", "Chocolate", "Almond", "Strawberry", "Other")
  pct <- round(slices/sum(slices)*100)
  lbls <- paste(lbls, pct)
  lbls <- paste(lbls,"%")
  pie(slices,labels = lbls, col=rainbow(length(lbls)), main="Pie Chart of Pies that are Pies")
  
  subAndQuad = function(input){
    input = input - 3
    input = input ^ 2
  }
  roww
  result = subAndQuad(roww)
  result
  
  
  balls = function(mr = 30, mw = 70, draw = 10){
    redLeft = 0;
    whiteLeft = 0;
    for(i in 0:draw){
      result = sample(mr + mw, size = 1, replace = TRUE)
      if(result < 31){
        redLeft = redLeft + 1
      }
      else whiteLeft = whiteLeft + 1
    }
    resultRed = redLeft / draw
    resultWhite = whiteLeft / draw
    return (c(resultRed, resultWhite))
  }
  
  result = balls()
  result
  
  vectorCreator = function(u){
    u = vector(mode = "double", length = 200)
    for(i in 0:200){
      sampleResult = sample(1:90, size = 40, replace = FALSE)
      medianResult = median(sampleResult)
      u[i] = medianResult
    }
    return (u)
  }
  u = vectorCreator(u)
  u
  
  
