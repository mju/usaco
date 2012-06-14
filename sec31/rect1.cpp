/*
ID: mickeyj1
TASK: rect1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>

#define MAX_NUM_COLORS 2500
#define INIT_COLOR 1

using namespace std;

class Rectangle {
public:
  Rectangle(int llx, int lly, int urx, int ury, int color=INIT_COLOR);
  ~Rectangle();
  bool intersect(const Rectangle& other) const;
  /* decomposes *this based on other, and push_front the pieces to
   * rects.
   * returns false if *this doesn't intersect with other; true otherwise.
   */
  bool decompose(const Rectangle& other, list<Rectangle>& rects) const;
  int unit_area();
  int get_color();

private:
  int m_llx;/* lower left x. */
  int m_lly;
  int m_urx;/* upper right x. */
  int m_ury;
  int m_color;
};

Rectangle::Rectangle(int llx, int lly, int urx, int ury, int color)
: m_llx(llx), m_lly(lly), m_urx(urx), m_ury(ury), m_color(color) {
}

Rectangle::~Rectangle() {
}

bool
Rectangle::intersect(const Rectangle& other) const {
  return !(
    other.m_ury <= m_lly ||
    other.m_lly >= m_ury ||
    other.m_urx <= m_llx ||
    other.m_llx >= m_urx
  );
}

bool
Rectangle::decompose(const Rectangle& other, list<Rectangle>& rects) const {
  if (!intersect(other)) {
    return false;
  }
  Rectangle intersection(
    other.m_llx < m_llx? m_llx: other.m_llx,
    other.m_lly < m_lly? m_lly: other.m_lly,
    other.m_urx > m_urx? m_urx: other.m_urx,
    other.m_ury > m_ury? m_ury: other.m_ury,
    other.m_color
  );
  /* get the four pieces.
   * ******************
   * *       0        *
   * ******************
   * *   *        *   *
   * * 3 * inter- * 1 *
   * *   * section*   *
   * *   *        *   *
   * ******************
   * *       2        *
   * ******************
   */
  Rectangle rect0(m_llx, intersection.m_ury, m_urx, m_ury, m_color);
  /* make sure rect0 has non-zero area. */
  if (rect0.m_llx != rect0.m_urx && rect0.m_lly != rect0.m_ury) {
    rects.push_front(rect0);
  }
  Rectangle rect1(
    intersection.m_urx, intersection.m_lly, m_urx, intersection.m_ury, m_color
  );
  if (rect1.m_llx != rect1.m_urx && rect1.m_lly != rect1.m_ury) {
    rects.push_front(rect1);
  }
  Rectangle rect2(m_llx, m_lly, m_urx, intersection.m_lly, m_color);
  if (rect2.m_llx != rect2.m_urx && rect2.m_lly != rect2.m_ury) {
    rects.push_front(rect2);
  }
  Rectangle rect3(
    m_llx, intersection.m_lly, intersection.m_llx, intersection.m_ury, m_color
  );
  if (rect3.m_llx != rect3.m_urx && rect3.m_lly != rect3.m_ury) {
    rects.push_front(rect3);
  }

  return true;
}

int
Rectangle::unit_area() {
  return (m_urx - m_llx) * (m_ury - m_lly);
}

int
Rectangle::get_color() {
  return m_color;
}

int
main(int argc, char** argv, char** envp) {
  int width, length, num_rects;
  int llx, lly, urx, ury, color;
  int colors[MAX_NUM_COLORS + 1] = {0};
  list<Rectangle> rects;

  fstream fin("rect1.in", ios::in);
  fin >> width >> length >> num_rects;
  rects.push_back(Rectangle(0, 0, width, length));
  for (int i = 0; i < num_rects; i++) {
    fin >> llx >> lly >> urx >> ury >> color;
    Rectangle rect(llx, lly, urx, ury, color);
    list<Rectangle>::iterator biter = rects.begin();
    const list<Rectangle>::iterator eiter = rects.end();
    while (biter != eiter) {
      if (!biter->decompose(rect, rects)) {
        biter++;
        continue;
      }
      biter = rects.erase(biter);
    }
    rects.push_back(rect);
  }
  fin.close();

  list<Rectangle>::iterator biter = rects.begin();
  const list<Rectangle>::iterator eiter = rects.end();
  for (; biter != eiter; biter++) {
    colors[biter->get_color()] += biter->unit_area();
  }

  fstream fout("rect1.out", ios::out);
  for (int i = 1; i <= MAX_NUM_COLORS; i++) {
    if (colors[i]) {
      fout << i << ' ' << colors[i] << endl;
    }
  }
  fout.close();

  return EXIT_SUCCESS;
}
