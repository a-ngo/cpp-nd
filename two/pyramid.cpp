#include <cassert>
#include <stdexcept>

class Pyramid {
    public:
        Pyramid(int length, int width, int height):
                m_length{length},
                m_width{width},
                m_height{height}{         
                    if (length < 0 || width < 0 || height <0){
                        throw std::invalid_argument( "received negative value" );
                    }
            };
        int Length(){
            return m_length;
        }
        int Width(){
            return m_width;
        }
        int Height(){
            return m_height;
        }
        double Volume(){return (m_length*m_width*m_height)/3.0;}
    private:
        int m_length;
        int m_width;
        int m_height;
};


int main() {
  Pyramid pyramid(4, 5, 6);
  assert(pyramid.Length() == 4);
  assert(pyramid.Width() == 5);
  assert(pyramid.Height() == 6);
  assert(pyramid.Volume() == 40);

  bool caught{false};
  try {
    Pyramid invalid(-1, 2, 3);
  } catch (...) {
    caught = true;
  }
  assert(caught);
}