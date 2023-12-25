package tetris.logic

import org.graalvm.compiler.nodeinfo.StructuralInput.Anchor

import scala.collection.mutable.ArrayBuffer


abstract class Tetromino(blockId : Int, gridDims : Dimensions) {

  def findOffset(currentBlockNum: Int): ArrayBuffer[Point] = {
    currentBlockNum match {
      case 0 => ArrayBuffer(Point(-1, 0), Point(0, 0), Point(1, 0), Point(2, 0))
      case 1 => ArrayBuffer(Point(-1, -1), Point(-1, 0), Point(0, 0), Point(1, 0))
      case 2 => ArrayBuffer(Point(-1, 0), Point(0, 0), Point(1, 0), Point(1, -1))
      case 3 => ArrayBuffer(Point(0, -1), Point(0, 0), Point(1, -1), Point(1, 0))
      case 4 => ArrayBuffer(Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1))
      case 5 => ArrayBuffer(Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1))
      case 6 => ArrayBuffer(Point(-1, -1), Point(0, -1), Point(0, 0), Point(1, 0))
    }
  }

  //var offset : Point = Point(0,0)
  var offsetBlock : ArrayBuffer[Point] = findOffset(blockId)

  def rotateRightOffset(offsetBlock : ArrayBuffer[Point]) : ArrayBuffer[Point] = {
    offsetBlock.map(point => Point(-point.y, point.x))
  }

  def rotateLeftOffset(offsetBlock: ArrayBuffer[Point]): ArrayBuffer[Point] = {
    offsetBlock.map(point => Point(point.y, -point.x))
  }

  def buildBlock(anchor: Point): ArrayBuffer[Point] = {
   offsetBlock.map(point => Point(point.x + anchor.x, point.y + anchor.y))
  }

  def rotateRight(block: ArrayBuffer[Point], anchor : Point) : ArrayBuffer[Point]
  def rotateLeft(block: ArrayBuffer[Point], anchor : Point) : ArrayBuffer[Point]


  def moveLeftAnchor(anchor: Point): Point = {
    val newX = anchor.x - 1
    val newY = anchor.y
    Point(newX, newY)
  }

  def moveLeftBlock(currentBlock: ArrayBuffer[Point]): ArrayBuffer[Point] = {
    currentBlock.map(point => point.copy(x = point.x - 1))
  }

  def moveRightAnchor(anchor: Point): Point = {
    val newX = anchor.x + 1
    val newY = anchor.y
    Point(newX, newY)
  }

  def moveRightBlock(currentBlock: ArrayBuffer[Point]): ArrayBuffer[Point] = {
    currentBlock.map(point => point.copy(x = point.x + 1))
  }

  def moveDownAnchor(anchor: Point): Point = {
    val newX = anchor.x
    val newY = anchor.y + 1
    Point(newX, newY)
  }

  def moveDownBlock(currentBlock: ArrayBuffer[Point]): ArrayBuffer[Point] = {
    currentBlock.map(point => point.copy(y = point.y + 1))
  }

}

class JLSTZ(blockId : Int, gridDims : Dimensions) extends Tetromino(blockId, gridDims) {
  override def rotateRight(block: ArrayBuffer[Point], anchor : Point): ArrayBuffer[Point] = {
    offsetBlock = rotateRightOffset(offsetBlock)
    val newBlock = buildBlock(anchor)
    newBlock
  }

  override def rotateLeft(block: ArrayBuffer[Point], anchor: Point): ArrayBuffer[Point] = {
    offsetBlock = rotateLeftOffset(offsetBlock)
    val newBlock = buildBlock(anchor)
    newBlock
  }
}

class O(blockId : Int, gridDims : Dimensions) extends Tetromino(blockId, gridDims) {
  override def rotateRight(block: ArrayBuffer[Point], anchor : Point): ArrayBuffer[Point] = block
  override def rotateLeft(block: ArrayBuffer[Point], anchor: Point): ArrayBuffer[Point] = block
}

class I(blockId : Int, gridDims : Dimensions) extends Tetromino(blockId, gridDims) {

  override def rotateRightOffset(offsetBlock: ArrayBuffer[Point]): ArrayBuffer[Point] = {
    offsetBlock.map(point => Point(-point.y + 1, point.x))
  }

  override def rotateRight(block: ArrayBuffer[Point], anchor: Point): ArrayBuffer[Point] = {
    offsetBlock = rotateRightOffset(offsetBlock)
    val newBlock = buildBlock(anchor)
    newBlock
  }

  override def rotateLeftOffset(offsetBlock: ArrayBuffer[Point]): ArrayBuffer[Point] = {
    offsetBlock.map(point => Point(point.y, -point.x + 1))
  }

  override def rotateLeft(block: ArrayBuffer[Point], anchor: Point): ArrayBuffer[Point] = {
    offsetBlock = rotateLeftOffset(offsetBlock)
    val newBlock = buildBlock(anchor)
    newBlock
  }
}