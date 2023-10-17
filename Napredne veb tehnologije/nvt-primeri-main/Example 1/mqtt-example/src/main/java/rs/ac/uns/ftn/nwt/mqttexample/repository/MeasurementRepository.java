package rs.ac.uns.ftn.nwt.mqttexample.repository;

import org.springframework.data.domain.Pageable;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;
import rs.ac.uns.ftn.nwt.mqttexample.model.Measurement;

import java.util.List;


@Repository
public interface MeasurementRepository extends CrudRepository<Measurement, Long> {
    List<Measurement> findByTopic(String topic, Pageable pageable);
}
