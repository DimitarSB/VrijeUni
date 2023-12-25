package tetris.logic

import engine.random.{RandomGenerator, ScalaRandomGen}
import tetris.logic.TetrisLogic._
import scala.collection.mutable.ArrayBuffer


class TetrisLogic(val randomGen: RandomGenerator,
                  val gridDims : Dimensions,
                  val initialBoard: Seq[Seq[CellType]]) {

  def this(random: RandomGenerator, gridDims : Dimensions) =
    this(random, gridDims, makeEmptyBoard(gridDims))

  def this() =
    this(new ScalaRandomGen(), DefaultDims, makeEmptyBoard(DefaultDims))


  //Random Number Gen
  var blockId: Int = randomGen.randomInt(7)

  //Grid
  var grid: Seq[Seq[CellType]] = initialBoard // use this to rewrite the grid structure, you need it to see the initial state of the board


  //Class initialisation
  var jlstz: JLSTZ = new JLSTZ(blockId, gridDims)
  var i : I = new I(blockId, gridDims)
  var o : O = new O(blockId, gridDims)

  //Base Block Points
  val startingPoint: Point = Point(findMiddle, 1)
  var anchor : Point = startingPoint

  def startingPoints(currentBlockNum: Int): ArrayBuffer[Point] = {
    currentBlockNum match {
      case 0 => ArrayBuffer(Point(-1, 0), Point(0,0), Point(1, 0), Point(2, 0))
      case 1 => ArrayBuffer(Point(-1, -1), Point(-1, 0), Point(0,0), Point(1, 0))
      case 2 => ArrayBuffer(Point(-1, 0), Point(0,0), Point(1, 0), Point(1, -1))
      case 3 => ArrayBuffer(Point(0, -1), Point(0,0), Point(1, -1), Point(1, 0))
      case 4 => ArrayBuffer(Point(-1, 0), Point(0,0), Point(0, -1), Point(1, -1))
      case 5 => ArrayBuffer(Point(-1, 0), Point(0,0), Point(1, 0), Point(0, -1))
      case 6 => ArrayBuffer(Point(-1, -1), Point(0, -1),Point(0,0), Point(1, 0))
    }
  }

  val cellTypeMap: Map[Int, CellType] = Map(
    0 -> ICell,
    1 -> JCell,
    2 -> LCell,
    3 -> OCell,
    4 -> SCell,
    5 -> TCell,
    6 -> ZCell
  )

  var currentBlock : ArrayBuffer[Point] = startingPoints(blockId)
  currentBlock = jlstz.buildBlock(anchor)

  def findMiddle: Int = {
    if (gridDims.width % 2 == 0) {
      (gridDims.width / 2) - 1
    }
    else (gridDims.width - 1) / 2
  }

  def collided(block: ArrayBuffer[Point]): Boolean = {
    val collided = block.exists { point => point.y == gridDims.height || grid(point.y)(point.x) != Empty}
    collided
  }

  def canRotateLeft(currentBlock: ArrayBuffer[Point], forI: Boolean): Boolean = {
    var rotatedBlock: ArrayBuffer[Point] = ArrayBuffer.empty[Point]
    if(forI){
      rotatedBlock = i.rotateLeft(currentBlock, anchor)
      i.rotateRight(currentBlock, anchor)
    }
    else {
      rotatedBlock = jlstz.rotateLeft(currentBlock, anchor)
      jlstz.rotateRight(currentBlock, anchor)
    }

    val isInBounds = rotatedBlock.forall { point =>
      point.x >= 0 && point.x < gridDims.width && point.y >= 0 && point.y < gridDims.height && !collided(rotatedBlock)
    }
    isInBounds
  }

  // TODO implement me
  def rotateLeft(): Unit = {
    if (isGameOver) {}
    else {
      blockId match {
        case 1 | 2 | 4 | 5 | 6 =>
          if(canRotateLeft(currentBlock, forI = false))
          currentBlock = jlstz.rotateLeft(currentBlock, anchor)
        case 3 => currentBlock = o.rotateLeft(currentBlock, anchor)
        case 0 =>
          if(canRotateLeft(currentBlock, forI = true))
          currentBlock = i.rotateLeft(currentBlock, anchor)
      }
    }
  }

  def canRotateRight(currentBlock: ArrayBuffer[Point], forI: Boolean): Boolean = {
    var rotatedBlock: ArrayBuffer[Point] = ArrayBuffer.empty[Point]
    if (forI) {
      rotatedBlock = i.rotateRight(currentBlock, anchor)
      i.rotateLeft(currentBlock, anchor)
    }
    else {
      rotatedBlock = jlstz.rotateRight(currentBlock, anchor)
      jlstz.rotateLeft(currentBlock, anchor)
    }

    val isInBounds = rotatedBlock.forall { point =>
      point.x >= 0 && point.x < gridDims.width && point.y >= 0 && point.y < gridDims.height && !collided(rotatedBlock)
    }
    isInBounds
  }

  // TODO implement me
  def rotateRight(): Unit = {
    if (isGameOver) {}
    else {
      blockId match {
        case 1 | 2 | 4 | 5 | 6 =>
          if(canRotateRight(currentBlock, forI = false))
          currentBlock = jlstz.rotateRight(currentBlock, anchor)
        case 3 => currentBlock = o.rotateRight(currentBlock, anchor)
        case 0 =>
          if(canRotateRight(currentBlock, forI = true))
          currentBlock = i.rotateRight(currentBlock, anchor)
      }
    }
  }

  def canMoveLeft(currentBlock: ArrayBuffer[Point]): Boolean = {
    val movedBlock = jlstz.moveLeftBlock(currentBlock)

    val noCollision = movedBlock.forall { point =>
      point.x >= 0 && point.x < gridDims.width &&
        point.y >= 0 && point.y < gridDims.height &&
        grid(point.y)(point.x) == Empty
    }

    noCollision
  }

  // TODO implement me
  def moveLeft(): Unit = {
      if (!isGameOver && canMoveLeft(currentBlock)) {
        currentBlock = jlstz.moveLeftBlock(currentBlock)
        anchor = jlstz.moveLeftAnchor(anchor)
      }
  }

  def canMoveRight(currentBlock: ArrayBuffer[Point]): Boolean = {
    val movedBlock = jlstz.moveRightBlock(currentBlock)
    jlstz.moveLeftBlock(currentBlock)

    val noCollision = movedBlock.forall { point => point.x < gridDims.width && grid(point.y)(point.x) == Empty}
    noCollision
  }


  // TODO implement me
  def moveRight(): Unit = {
    if (isGameOver) {}
    else {
      if (canMoveRight(currentBlock)) {
        currentBlock = jlstz.moveRightBlock(currentBlock)
        anchor = jlstz.moveRightAnchor(anchor)
      }
    }

  }

  def spawnBlock(): Unit = {
    blockId = randomGen.randomInt(7)
    jlstz = new JLSTZ(blockId, gridDims)
    i = new I(blockId, gridDims)
    o = new O(blockId, gridDims)
    anchor = startingPoint
    currentBlock = startingPoints(blockId)
    currentBlock = jlstz.buildBlock(anchor)
  }

  // TODO implement me
  def moveDown(): Unit = {
    if (isGameOver) {}
    else {
      anchor = jlstz.moveDownAnchor(anchor)
      val movedBlock = jlstz.moveDownBlock(currentBlock)

      if (collided(movedBlock)) {
        for (point <- movedBlock) {
          val cellType = cellTypeMap(blockId)
          grid = grid.updated(point.y, grid(point.y).updated(point.x, cellType))
        }

        grid = clearTetris(grid)
        spawnBlock()
      }
      else currentBlock = movedBlock.clone()
    }
  }

  def clearTetris(grid: Seq[Seq[CellType]]): Seq[Seq[CellType]] = {
    var newGrid = grid
    var clearedRows = 0

    for (i <- gridDims.height - 1 to 0 by -1) {
      if (!grid(i).contains(Empty)) {
        clearedRows += 1
      } else {
        // Copy the row to newGrid
        newGrid = newGrid.updated(gridDims.height - clearedRows - 1, grid(i))
      }
    }

    // Fill cleared rows with empty cells
    val emptyRow = Seq.fill(gridDims.width)(Empty)
    for (i <- 0 until clearedRows) {
      newGrid = newGrid.updated(i, emptyRow)
    }

    newGrid
  }


  // TODO implement me
  def doHardDrop(): Unit = {
    if (isGameOver) {}
    else {
      var movedBlock = currentBlock
      var movedAnchor = anchor

      while (!collided(jlstz.moveDownBlock(movedBlock))) {
        movedBlock = jlstz.moveDownBlock(movedBlock)
        movedAnchor = jlstz.moveDownAnchor(movedAnchor)
      }

      for (point <- movedBlock) {
        val cellType = cellTypeMap(blockId)
        grid = grid.updated(point.y, grid(point.y).updated(point.x, cellType))
      }

      grid = clearTetris(grid)
      spawnBlock()
    }
  }

  // TODO implement me
  def isGameOver: Boolean = {
    val testSpawn: ArrayBuffer[Point] = startingPoints(blockId).map(point => Point(point.x + startingPoint.x, point.y + startingPoint.y))
//    println(testSpawn)
//    testSpawn.foreach(point=> if (testGrid(point.y)(point.x) != Empty) {println("FAIL HERE " + testGrid(point.y)(point.x) + point)})
    testSpawn.exists { point =>grid(point.y)(point.x) != Empty}
  }

  // TODO implement me
  def getCellType(p: Point): CellType = {
    val blockCellType = if (currentBlock.contains(p)) cellTypeMap(blockId) else Empty
    val gridCellType = grid.lift(p.y).flatMap(_.lift(p.x)).getOrElse(Empty)

    if (blockCellType != Empty) blockCellType
    else gridCellType

    // getCellType should only look like that below, don't overcomplicate it
//    if (currentBlock.contains(p)) cellTypeMap(blockId)
//    else grid(p.x)(p.y)
    //------------------------------
  }

}

object TetrisLogic {

  val FramesPerSecond: Int = 3 // change this to speed up or slow down the game

  val DrawSizeFactor = 1.8 // increase this to make the game bigger (for high-res screens)
  // or decrease to make game smaller



  def makeEmptyBoard(gridDims : Dimensions): Seq[Seq[CellType]] = {
    val emptyLine = Seq.fill(gridDims.width)(Empty)
    Seq.fill(gridDims.height)(emptyLine)
  }


  // These are the dimensions used when playing the game.
  // When testing the game, other dimensions are passed to
  // the constructor of GameLogic.
  //
  // DO NOT USE the variable DefaultGridDims in your code!
  //
  // Doing so will cause tests which have different dimensions to FAIL!
  //
  // In your code only use gridDims.width and gridDims.height
  // do NOT use DefaultDims.width and DefaultDims.height


  val DefaultWidth: Int = 15
  val NrTopInvisibleLines: Int = 4
  val DefaultVisibleHeight: Int = 20
  val DefaultHeight: Int = DefaultVisibleHeight + NrTopInvisibleLines
  val DefaultDims : Dimensions = Dimensions(width = DefaultWidth, height = DefaultHeight)


  def apply() = new TetrisLogic(new ScalaRandomGen(),
    DefaultDims,
    makeEmptyBoard(DefaultDims))

}