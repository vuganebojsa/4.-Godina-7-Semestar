package rs.ac.uns.ftn.nwt.influxdbexample.configuration;

import com.influxdb.client.InfluxDBClient;
import com.influxdb.client.InfluxDBClientFactory;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.env.Environment;

@Configuration
public class InfluxDbConfiguration {
    private final String url;
    private final String token;
    private final String organization;
    private final String bucket;

    public InfluxDbConfiguration(Environment env) {
        this.url = String.format("http://%s:%s", env.getProperty("influxdb.host"),
                env.getProperty("influxdb.port"));
        this.token = env.getProperty("influxdb.token");
        this.organization = env.getProperty("influxdb.organization");
        this.bucket = env.getProperty("influxdb.bucket");
    }

    @Bean
    public InfluxDBClient influxDbClient() {
        return InfluxDBClientFactory.create(this.url, this.token.toCharArray(),
                this.organization, this.bucket);
    }
}
