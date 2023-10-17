package rs.ac.uns.ftn.nwt.mqttexample.service;

import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;
import rs.ac.uns.ftn.nwt.mqttexample.model.Measurement;
import rs.ac.uns.ftn.nwt.mqttexample.repository.MeasurementRepository;

import java.util.List;

@Service
public class MeasurementService {

    private final MeasurementRepository measurementRepository;

    public MeasurementService(MeasurementRepository measurementRepository) {
        this.measurementRepository = measurementRepository;
    }

    public List<Measurement> findByTopic(String topic) {
        Pageable pageable = PageRequest.of(0, 10, Sort.Direction.DESC, "id");
        return this.measurementRepository.findByTopic(topic, pageable);
    }

    public Measurement save(Measurement measurement) {
        return this.measurementRepository.save(measurement);
    }
}
