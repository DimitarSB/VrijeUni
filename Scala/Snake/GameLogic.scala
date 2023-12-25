package snake.logic

//import scala.util.Random

import engine.random.{RandomGenerator, ScalaRandomGen}
import snake.logic.GameLogic._

import scala.collection.mutable.ArrayBuffer
import scala.util.Random

class GameFrame(val fullSnake: ArrayBuffer[Point] = ArrayBuffer(Point(0, 0), Point(1, 0), Point(2, 0)), val applePos: Int = 0) {

  def createFrame: GameFrame = {
    new GameFrame(fullSnake, applePos)
  }
}

class GameLogic(val random: RandomGenerator, val gridDims: Dimensions) {

  //Snake Head
  var snakeCoordinates: Point = Point(2, 0)
  var snakeDirection: Direction = East()

  //Snake moves
  var moveAllowed: Boolean = true
  var bufferForSnakeSteps: ArrayBuffer[Point] = ArrayBuffer(Point(0, 0), Point(1, 0), snakeCoordinates)

  //Snake Body
  var bodyLength = 3

  //Apple
  var check = false
  var freePoints: ArrayBuffer[Point] = findFreeSpaces()
  var applePlacement: Int = -1
  var starterApple: Int = -1
  if(!freePoints.isEmpty) {
    println("goHere")
    applePlacement = random.randomInt(freePoints.size)
    starterApple = applePlacement
  }


  //Game State
  var reverseOn: Boolean = false
  var frameStack: List[GameFrame] = Nil

  def pushFrame(gameFrame: GameFrame): Unit = {
    var newFrame = gameFrame.createFrame
    frameStack = newFrame :: frameStack
  }

  def findFreeSpaces(): ArrayBuffer[Point] = {

    var freePoints: ArrayBuffer[Point] = ArrayBuffer()
    for (y <- 0 until gridDims.height; x <- 0 until gridDims.width) {
      println("enter loop")
      val isFree = !bufferForSnakeSteps.contains(Point(x, y))
      if (isFree) {
        freePoints.addOne(Point(x, y))
      }
    }

    freePoints
  }



  def gameOver: Boolean = {

    var i = 0
    for (i <- 0 until (bufferForSnakeSteps.size - 1)) {
      if (snakeCoordinates == bufferForSnakeSteps(i)) {
        return true
      }
    }
    if (check) return true
    return false
  }

  def step(): Unit = {

    moveAllowed = true
    if (gameOver) {
//      wait(1)
    }
    else if (reverseOn) {
      if (frameStack.isEmpty) {
        resetSnake()
      }
      else swapFrames()
    }
    else {
      var x = snakeCoordinates.x
      var y = snakeCoordinates.y

      if (isSnakeOnEdge(x, y)) {
        snakeMoveEdge(x, y)
        bufferForSnakeSteps += snakeCoordinates
        canSnakeGrow()
      }
      else {
        snakeMoveNoEdge(x, y)
        bufferForSnakeSteps += snakeCoordinates
        canSnakeGrow()
      }
        appleEaten()
    }
    pushFrame(new GameFrame(bufferForSnakeSteps, applePlacement))
  }

  private def resetSnake(): Unit = {
      bufferForSnakeSteps = ArrayBuffer(Point(0, 0), Point(1, 0), Point(2, 0))
    applePlacement = starterApple
  }

  private def swapFrames(): Unit = {

    val previousFrame = frameStack.head
    bufferForSnakeSteps.clear()
    bufferForSnakeSteps ++= previousFrame.fullSnake
    applePlacement = previousFrame.applePos
    frameStack = frameStack.tail
  }

  private def isSnakeOnEdge(x: Int, y: Int): Boolean = {

    if (x == gridDims.width - 1 && snakeDirection == East() | x == 0 && snakeDirection == West()
      | y == 0 && snakeDirection == North() | y == gridDims.height - 1 && snakeDirection == South()) {
      return true
    }
    false
  }

  private def snakeMoveEdge(x: Int, y: Int): Unit = {

    snakeDirection match {
      case East() => snakeCoordinates = Point(0, y)
      case West() => snakeCoordinates = Point(gridDims.width - 1, y)
      case South() => snakeCoordinates = Point(x, 0)
      case North() => snakeCoordinates = Point(x, gridDims.height - 1)
    }
  }

  private def snakeMoveNoEdge(x: Int, y: Int): Unit = {

    snakeDirection match {
      case East() => snakeCoordinates = Point(x + 1, y)
      case West() => snakeCoordinates = Point(x - 1, y)
      case North() => snakeCoordinates = Point(x, y - 1)
      case South() => snakeCoordinates = Point(x, y + 1)
    }
  }

  private def canSnakeGrow(): Unit = {

    if (bodyLength != 3) {
      bodyLength = bodyLength + 1
    }
    else bufferForSnakeSteps = bufferForSnakeSteps.drop(1)
  }

  private def appleEaten(): Unit = {

    if (!freePoints.isEmpty) {
      if (snakeCoordinates == freePoints(applePlacement)) {
        freePoints = findFreeSpaces()


        applePlacement = random.randomInt(freePoints.size)

        bodyLength = bodyLength - 3
      }
    }
  }

  def setReverse(r: Boolean): Unit = {
    reverseOn = r
  }

  def changeDir(d: Direction): Unit = {

    if (snakeDirection != d.opposite && moveAllowed) {
      snakeDirection = d
      moveAllowed = false
    }
  }

  def getCellType(p: Point): CellType = {

    if (p == snakeCoordinates) {
      SnakeHead(snakeDirection)
    } else if (p == bufferForSnakeSteps.last || bufferForSnakeSteps.contains(p)) {
      SnakeBody()
    } else if (p == freePoints(applePlacement) && freePoints.nonEmpty) {
      Apple()
    } else {
      Empty()
    }
  }

}

/** GameLogic companion object */
object GameLogic {

  val FramesPerSecond: Int = 5 // change this to increase/decrease speed of game

  val DrawSizeFactor = 1.0 // increase this to make the game bigger (for high-res screens)
  // or decrease to make game smaller

  // These are the dimensions used when playing the game.
  // When testing the game, other dimensions are passed to
  // the constructor of GameLogic.
  //
  // DO NOT USE the variable DefaultGridDims in your code!
  //
  // Doing so will cause tests which have different dimensions to FAIL!
  //
  // In your code only use gridDims.width and gridDims.height
  // do NOT use DefaultGridDims.width and DefaultGridDims.height
  val DefaultGridDims
  : Dimensions =
  Dimensions(width = 3, height = 1) // you can adjust these values to play on a different sized board

}

