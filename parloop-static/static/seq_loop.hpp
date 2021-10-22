#ifndef __SEQ_LOOP_H
#define __SEQ_LOOP_H

#include <functional>
#include <thread>

class SeqLoop {
public:
  /// @brief execute the function f multiple times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel
  void parfor (size_t beg, size_t end, size_t inc,
	       std::function<void(int)> f) {
          for (size_t i = beg; i < end; i += inc) {
              f(i);
          }
        } 

  /// @brief execute the function f multiple times with different
  /// parameters possibly in parallel
  ///
  /// f will be executed multiple times with parameters starting at
  /// beg, no greater than end, in inc increment. These execution may
  /// be in parallel.
  ///
  /// Each thread that participate in the calculation will have its
  /// own TLS object.
  ///
  /// Each thread will execute function before prior to any
  /// calculation on a TLS object.
  ///
  /// Each thread will be passed the TLS object it executed before on.
  ///
  /// Once the iterations are complete, each thread will execute after
  /// on the TLS object. No two thread can execute after at the same time.
  template<typename TLS>
  void parfor (size_t beg, size_t end, size_t increment,
	       std::function<void(TLS&)> before,
	       std::function<void(int, TLS&)> f,
	       std::function<void(TLS&)> after
	       ) {
           TLS tls;
           before(tls);
           for (size_t i=beg; i<end; i+= increment){
             f(i, tls);
           }
           after(tls);
          }
  
  float parforThreads (float lowerBound, float upperBound, int numOfPoints, int intensity, int nbthreads, std::function<float(float, int)> f) {
    if(nbthreads == 0)
      nbthreads = 1;

    int interval = 0;
    float finalValue = 0.0;

    while((numOfPoints % nbthreads) != 0) {
      nbthreads++;
    }

    interval = numOfPoints / nbthreads;
    std::vector<std::thread> threads (nbthreads);

    for(int j = 0; j < nbthreads; j++) {
      size_t start = j*interval;
      size_t finish = (interval*(j+1))-1;
      threads.push_back(std::thread(parfor, start, finish, 1,
			       [&](float& tls) -> void{
				 tls = 0.0;
			       },
			       [&](int i, float& tls) -> void{
				 float x = lowerBound + (i + 0.5) * (((upperBound-lowerBound)/numOfPoints));
				 tls += f(x, intensity);
			       },
			       [&](float tls) -> void{
				 finalValue += ((upperBound-lowerBound)/numOfPoints) * tls;
			       }));
    }

    for(auto& t: threads)
      t.join();

    return finalValue;
  }
};

#endif
