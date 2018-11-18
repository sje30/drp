data = read.table("~/langs/R/sjedrp/data/sjedrp.d30.txt", header=TRUE)
plot(data)

p = drp::autodrp(data$x, data$y, 10, 20)
p1 = sjedrp::autodrp(data$x, data$y, 10, 20)
require(sjedrp)

plot(p)
all.equal(p, p1)
