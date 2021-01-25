
#ifndef ARCTIC_TRAP_MANAGERS_HPP
#define ARCTIC_TRAP_MANAGERS_HPP

#include <valarray>

#include "ccd.hpp"
#include "traps.hpp"

class TrapManager {
   public:
    TrapManager(){};
    TrapManager(std::valarray<Trap> traps, int max_n_transfers, CCD ccd);
    ~TrapManager(){};

    std::valarray<Trap> traps;
    CCD ccd;

    std::valarray<double> watermark_volumes;
    std::valarray<double> watermark_fills;
    std::valarray<double> tmp_watermark_volumes;
    std::valarray<double> tmp_watermark_fills;
    std::valarray<double> stored_watermark_volumes;
    std::valarray<double> stored_watermark_fills;

    int n_traps;
    int max_n_transfers;
    int n_watermarks_per_transfer;
    int n_watermarks;
    int n_active_watermarks;
    int stored_n_active_watermarks;
    double empty_watermark;

    std::valarray<double> fill_probabilities_from_empty;
    std::valarray<double> fill_probabilities_from_full;
    std::valarray<double> fill_probabilities_from_release;

    void initialise_trap_states();
    void reset_trap_states();
    void store_trap_states();
    void restore_trap_states();

    void set_fill_probabilities_from_dwell_time(double dwell_time);
    double n_trapped_electrons_from_watermarks(
        std::valarray<double> wmk_volumes, std::valarray<double> wmk_fills);
    int watermark_index_above_cloud_from_volumes(
        std::valarray<double> wmk_volumes, double cloud_fractional_volume);
};

class TrapManagerInstantCapture : public TrapManager {
   public:
    TrapManagerInstantCapture(std::valarray<Trap> traps, int max_n_transfers, CCD ccd);
    ~TrapManagerInstantCapture(){};

    double n_electrons_released();
    double n_electrons_captured(double n_free_electrons);
    double n_electrons_released_and_captured(double n_free_electrons);
};

#endif  // ARCTIC_TRAP_MANAGERS_HPP
